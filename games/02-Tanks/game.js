
var game = new Phaser.Game(992, 480, Phaser.CANVAS, 'game');

var PhaserGame = function (game) {

	this.tank = null;
	this.turret = null;
	this.flame = null;
	this.bullet = null;

	this.background = null;
	this.targets = null;
	this.land = null;
	this.emitter = null;

	this.power = 300;
	this.powerText = null;

	this.cursors = null;
	this.fireButton = null;
};

PhaserGame.prototype = {

	init: function () {
		
		// This will stop Phaser from rendering graphics at sub-pixel locations, keeping them nice and crisp. 
		this.game.renderer.renderSession.roundPixels = true;
		
		// We'll also set the game world to be 992 pixels wide, enable physics and setting a gravity value of 200:
		this.game.world.setBounds(0, 0, 992, 480);

		this.physics.startSystem(Phaser.Physics.ARCADE);
		this.physics.arcade.gravity.y = 200;
	},

	preload: function () {

		// this.load.baseURL = 'http://files.phaser.io.s3.amazonaws.com/codingtips/issue002/';
		this.load.crossOrigin = 'anonymous';
        
        //  Note: Graphics from Amiga Tanx Copyright 1991 Gary Roberts
		this.load.image('tank', 'assets/tank.png');
		this.load.image('turret', 'assets/turret.png');
		this.load.image('bullet', 'assets/bullet.png');
		this.load.image('background', 'assets/background.png');
		this.load.image('flame', 'assets/flame.png');
		this.load.image('target', 'assets/target.png');
		this.load.image('land', 'assets/land.png');
	},

	create: function () {

		//  Simple but pretty background
		this.background = this.add.sprite(0, 0, 'background');

		//  The targets to hit (hidden behind the land slightly)
		this.targets = this.add.group(this.game.world, 'targets', false, true, Phaser.Physics.ARCADE);

		this.targets.create(284, 378, 'target');
		this.targets.create(456, 153, 'target');
		this.targets.create(545, 305, 'target');
		this.targets.create(726, 391, 'target');
		this.targets.create(972, 74, 'target');

		//  Stop gravity from pulling them away
        // setAll lets you quickly set the same property across all members of the Group. 
        // In this case we tell it to disable gravity.
		this.targets.setAll('body.allowGravity', false);

		//  The land is a BitmapData the size of the game world
		//  We draw the 'lang.png' to it then add it to the world
		this.land = this.add.bitmapData(992, 480);
		this.land.draw('land');
		this.land.update();
		this.land.addToWorld();

		//  A small burst of particles when a target is hit
        // It's re-using the flame.png which we use for the tank fire effect. 
        // Rotation is disabled by calling setRotation with no parameters. 
        // When the particles emit they'll pick a random x velocity between -120 and 120, 
        // and a vertical one between -100 and -200 (thrusting up into the air).
		this.emitter = this.add.emitter(0, 0, 30);
		this.emitter.makeParticles('flame');
		this.emitter.setXSpeed(-120, 120);
		this.emitter.setYSpeed(-100, -200);
		this.emitter.setRotation();

		//  A single bullet that the tank will fire
		this.bullet = this.add.sprite(0, 0, 'bullet');
		this.bullet.exists = false;
		this.physics.arcade.enable(this.bullet);

		//  The body of the tank
		this.tank = this.add.sprite(24, 383, 'tank');

		//  The turret which we rotate (offset 30x14 from the tank)
		this.turret = this.add.sprite(this.tank.x + 30, this.tank.y + 14, 'turret');

		//  When we shoot this little flame sprite will appear briefly at the end of the turret
		this.flame = this.add.sprite(0, 0, 'flame');
		this.flame.anchor.set(0.5);
		this.flame.visible = false;

		//  Used to display the power of the shot
		this.power = 300;
		this.powerText = this.add.text(8, 8, 'Power: 300', { font: "18px Arial", fill: "#ffffff" });
		this.powerText.setShadow(1, 1, 'rgba(0, 0, 0, 0.8)', 1);
		this.powerText.fixedToCamera = true;

        var txt = 'Turret: arrow up, down | Power: arrow left, right | Fire: space';
        this.introText = this.add.text(200, 8, txt, { font: "18px Arial", fill: "#000000" });
        
		//  Some basic controls
		this.cursors = this.input.keyboard.createCursorKeys();

		this.fireButton = this.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
		this.fireButton.onDown.add(this.fire, this);

	},

	/*** Called by update if the bullet is in flight. */
	bulletVsLand: function () {

		//  Simple bounds check
        // If the bullet goes out of bounds then we kill it and return
        // we don't check the 'top' of the world, as we want it to be allowed to rise up above the screen and fall back down again.
		if (this.bullet.x < 0 || this.bullet.x > this.game.world.width || this.bullet.y > this.game.height)
		{
			this.removeBullet();
			return;
		}

        // Because we're going to be doing a pixel color look-up on the BitmapData we have to floor the bullet coordinates. Once done we can use the BitmapData.getPixel method to get a Color object for the given pixel. This is done every frame as the bullet flies through the air, we sample the pixel color beneath it.
        // Our PNG is a landscape drawn on a transparent background, so all we need to do is check that we're over a pixel that has an alpha value greater than zero. If this is the case we blow a chunk out of the land.
        // This is done by setting the destination-out blend mode. If you draw on a canvas with this blend mode you can effectively "remove" parts of it. In this case we'e drawing a 16px sized circle where the bullet landed. Combine this with the blend mode and you punch a small hole into the land.
        // The final few lines reset the blend mode and call BitmapData.update which tells it to rescan the pixel data and render the new scene. Finally the bullet is removed, its job done.
        
		var x = Math.floor(this.bullet.x);
		var y = Math.floor(this.bullet.y);
		var rgba = this.land.getPixel(x, y);
		if (rgba.a > 0)
		{
			this.land.blendDestinationOut();
			this.land.circle(x, y, 16, 'rgba(0, 0, 0, 255');
			this.land.blendReset();
			this.land.update();
			//  If you like you could combine the above 4 lines:
			// this.land.blendDestinationOut().circle(x, y, 16, 'rgba(0, 0, 0, 255').blendReset().update();
			this.removeBullet();
		}
	},

	/*** Called by fireButton.onDown */
	fire: function () {

        // check if the bullet exists (i.e. is in flight),
		if (this.bullet.exists)
		{
			return;
		}

		//  Re-position the bullet where the turret is
		this.bullet.reset(this.turret.x, this.turret.y);

		//  Now work out where the END of the turret is
        // display the 'flame' sprite when they shoot
        // This allows you to calculate where the Point would be if it was rotated and moved from its origin. 
        // In the code above we set the rotation to match the turret, and the distance 34 pixels works for these assets. 
        // The end result is that the flame effect appears at the end of the gun, regardless of its angle of rotation.
		var p = new Phaser.Point(this.turret.x, this.turret.y);
		p.rotate(p.x, p.y, this.turret.rotation, false, 34);

		//  And position the flame sprite there
		this.flame.x = p.x;
		this.flame.y = p.y;
		this.flame.alpha = 1;
		this.flame.visible = true;

		//  Boom
		this.add.tween(this.flame).to( { alpha: 0 }, 100, "Linear", true);

		//  So we can see what's going on when the bullet leaves the screen
		this.camera.follow(this.bullet);

		//  Our launch trajectory is based on the angle of the turret and the power
        // The launch trajectory is based on the angle of the turret and the power the player has set. 
        // It will calculate the velocity need for these two factors and inject them into the velocity of the bullet.
		this.physics.arcade.velocityFromRotation(this.turret.rotation, this.power, this.bullet.body.velocity);

	},

	/** Called by physics.arcade.overlap if the bullet and a target overlap */
	hitTarget: function (bullet, target) {

        // activate the emitter 
        // The emitter is positioned on the center of the target Sprite and set to explode. 
        // The first parameter tells the flames to live for 2 seconds, the 2nd to explode 10 of them at once. 
		this.emitter.at(target);
		this.emitter.explode(2000, 10);

		target.kill();

        // This call to removeBullet passes a value of true. 
        // This tells the Camera tween to delay for a little longer before returning to the tank. 
        // It gives you a little more time to enjoy the effect :)
        this.removeBullet(true);
	},

	/*** Removes the bullet, stops the camera following and tweens the camera back to the tank. */
	removeBullet: function (hasExploded) {

		if (typeof hasExploded === 'undefined') { hasExploded = false; }

		this.bullet.kill();
		this.camera.follow();

		var delay = 1000;

		if (hasExploded)
		{
			delay = 2000;
		}

		this.add.tween(this.camera).to( { x: 0 }, 1000, "Quint", true, delay);

        // We need to stop the Camera tracking the bullet so that the tween works. 
        // The tween pauses for 1 second then tweens the Camera back to look at the tank again ready for the next shot. 
        // If you don't stop the Camera following the tween will seem to fail, 
        // because Camera tracking takes priority over positioning of it.
	},

	/**
	 * Core update loop. Handles collision checks and player input.
	 */
	update: function () {

		//  If the bullet is in flight we don't let them control anything
		if (this.bullet.exists)
		{
			//  check Bullet vs. Targets
			this.physics.arcade.overlap(this.bullet, this.targets, this.hitTarget, null, this);

			//  check Bullet vs. Land
			this.bulletVsLand();
		}
		else
		{
			//  Allow them to set the power between 100 and 600
			if (this.cursors.left.isDown && this.power > 100)
			{
				this.power -= 2;
			}
			else if (this.cursors.right.isDown && this.power < 600)
			{
				this.power += 2;
			}

			//  Allow them to set the angle, between -90 (straight up) and 0 (facing to the right)
			if (this.cursors.up.isDown && this.turret.angle > -90)
			{
				this.turret.angle--;
			}
			else if (this.cursors.down.isDown && this.turret.angle < 0)
			{
				this.turret.angle++;
			}

			//  Update the text
			this.powerText.text = 'Power: ' + this.power;
		}

	}

};

game.state.add('Game', PhaserGame, true);
