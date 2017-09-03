var StateMain = {
    
    preload: function () {
        
        // moved to state_load.js
        
//        // load paddle image
//        game.load.image('imgPaddle', 'img/paddle.png');
//        
//        // load ball
//        game.load.image('imgBall', 'img/ball.png');
//                
//        // load bricks
//        game.load.image('imgBrickGreen', 'img/brick_green.png');
//        game.load.image('imgBrickPurple', 'img/brick_purple.png');
//        game.load.image('imgBrickRed', 'img/brick_red.png');
//        game.load.image('imgBrickYellow', 'img/brick_yellow.png');
//        
//        // add background
//        game.load.image('imgBkg', 'img/bg_blue.png');
//        game.load.image('imgBlack', 'img/bg_black.png');
//        
//        
//        // load audio
//        game.load.audio('sfxHitBrick','snd/fx_hit_brick.wav');
//        game.load.audio('sfxHitPaddle','snd/fx_hit_paddle.wav');
//        game.load.audio('sfxLoseLife','snd/fx_lose_life.ogg');
//        game.load.audio('bgmMusic','snd/bgm_electric_air.ogg');

        // start the physics
        game.physics.startSystem(Phaser.Physics.ARCADE);
        // turn down the collision with the bottom of the world
        game.physics.arcade.checkCollision.down = false;
        
        this.lives = 3;
        this.points = 0;
        
    },
    
    create: function () {
        
        // for mobile
        this.touchOldX = undefined;
        this.touchNewX = undefined;
        this.touchActive = false;
        this.touchMove = 0;
        
        // add background
        var w = game.world.width;
        var h = game.world.height;
        this.bkg = game.add.tileSprite(0, 0, w, h, 'imgBkg');
        
        // set the velocity X to 500px/sec
        this.paddleVelX = 500 / 1000;  // 500px/sec
        // store previous mouse position
        this.prevX = game.input.x;
        
        // handling the touch movement
        if (game.device.touch && this.touchActive) {
            
            this.touchOldX = this.touchNewX;
            this.touchNewX = game.input.x;
            this.touchMove = 0;
            if (this.touchOldX != undefined && this.touchNewX != undefined) {
                this.touchMove = this.touchNewX - this.touchOldX;
            }
            this.paddle.x += this.touchMove;
        }
        
        // add the paddle to the screen
        this.paddle = game.add.sprite(0, 0, 'imgPaddle');
        
        // set anchor point to bottom-center
        this.paddle.anchor.setTo(0.5, 1);
        this.paddleHalf = this.paddle.width / 2;

        // create the ball
        this.ball = game.add.sprite(0, 0, 'imgBall');

        // Enable the physics system on the ball
        game.physics.arcade.enable(this.ball);
        this.ball.body.enable = true;
        this.ball.body.bounce.set(1);
        this.ball.body.collideWorldBounds = true;
        
        this.ball.isShot = false;
        this.ball.iniVelX = 200;
        this.ball.iniVelY = -300;
        
        // Enable the ball to check whether it is inside the world bounds
        this.ball.checkWorldBounds = true;
        this.ball.events.onOutOfBounds.add(this.loseLife, this);
        
        
        // Enable the physics system on the paddle
        game.physics.arcade.enable(this.paddle);
        this.paddle.body.enable = true;
        // make it immovable to the ball's collision
        this.paddle.body.immovable = true;
        
        // reset the paddle into its original position
        this.resetPaddle();
        
        // create black-line TileSprite
        h = this.paddle.height;
        var blackLine = game.add.tileSprite(0, 0, w, h, 'imgBlack');
        blackLine.anchor.set(0, 1);
        blackLine.y = game.world.height;
        
        this.txtLives = game.add.text(0, 0, g_txtLives + this.lives);
        this.txtLives.fontSize = 18;
        this.txtLives.fill = "#ffffff";
        this.txtLives.align = "left";
        this.txtLives.font = "sans-serif";
        this.txtLives.anchor.set(0, 1);
        this.txtLives.y = game.world.height;
        
        // JavaScript objects are passed by reference.
        var txtConfig = {
            font: "18px Overlock",
            fill: "#ffffff",
            align: "right"
        };
        this.txtPoints = game.add.text(0, 0, this.points + g_txtPoints, txtConfig);
        this.txtPoints.anchor.set(1);
        this.txtPoints.x = game.world.width;
        this.txtPoints.y = game.world.height;
        
        // audio
        this.sfxHitBrick = game.add.audio('sfxHitBrick');
        this.sfxHitPaddle = game.add.audio('sfxHitPaddle');
        this.sfxLoseLife = game.add.audio('sfxLoseLife')
        this.bgmMusic = game.add.audio('bgmMusic');

    
        // audio
//        this.bgmMusic.loop = true;
//        this.bgmMusic.play();
        
        
        // Bricks
        
        // group of sprites
        this.bricks = game.add.group();

        // Enable the physics system on the group of bricks
        this.bricks.enableBody = true;
        this.bricks.bodyType = Phaser.Physics.ARCADE;
        
        var brickImages = [
            'imgBrickGreen',
            'imgBrickPurple',
            'imgBrickRed',
            'imgBrickYellow'
        ];
        
        this.numCols = 10;
        this.numRows = 4;
        
        // place bicks at (0,0)
        var i, j;
        for (i = 0; i < this.numRows; i++) {
            var img = brickImages[i];
            for (j = 0; j < this.numCols; j++) {
                
                var brick = this.bricks.create(0, 0, img);
                
                // set the immovable probperty on the bricks
                brick.body.immovable = true;
                
                // set brick position
                brick.x = brick.width * j;
                brick.y = brick.height * i;
            }
        }
        
        // enable shoot via mouse click
        game.input.onDown.add(this.shootBall, this);
        
        // for mobile
        game.input.onDown.add(this.onDown, this);
        game.input.onUp.add(this.onUp, this);

    },

    onDown: function () {
        
        this.shootBall();
        this.touchActive = true;
        
    },
    
    onUp: function () {
        
        this.touchOldX = undefined;
        this.touchNewX = undefined;
        this.touchActive = false;
        
    },
    
    shootBall: function () {
        
        if (this.ball.isShot)
            return;
        this.ball.isShot = true;
        var velArray = [1, -1];
        var rand = Math.random() * velArray.length;
        rand = Math.floor(rand);
        var vel = velArray[rand];
        var x = this.ball.iniVelX * vel;
        var y = this.ball.iniVelY;
        this.ball.body.velocity.set(x,y);
        this.ball.isShot = true;

        // play sound
        this.sfxHitPaddle.play();
        
    },
    
    removeBrick: function (ball, brick) {
        
        // Killing a sprite doesn’t delete it from memory, it justs turns off three boolean variables regarding its alive state
        brick.kill();
        
        this.points += 10;
        this.txtPoints.text = this.points + g_txtPoints;
        this.sfxHitBrick.play();
        
        // countLiving is part of the GroupObject
        if (this.bricks.countLiving() == 0) {
            this.goToOver();
        }
        
    },

    hitPaddle: function (ball, paddle) {
        
        this.sfxHitPaddle.play();
        
    },

    goToOver: function () {
        
        this.bgmMusic.stop();
        
        game.lives = this.lives;
        game.points = this.points;
        
        game.state.start('StateOver');
    },
    
    loseLife: function () {

        this.resetPaddle();
        this.lives -= 1;
        this.txtLives.text = g_txtLives + this.lives;
        
        this.sfxLoseLife.play();
        
        console.log('Lives:' + this.lives);
        
        if (this.lives == 0) {
            this.goToOver();
        }
        
    },

    update: function () {
        // update function keeps running as long as the brower tab is focused
        // this is the game loop
        
        // define the collisions in the physics system
        //game.physics.arcade.collide(this.ball, this.paddle);
        game.physics.arcade.collide(this.ball, this.paddle, this.hitPaddle, null, this);
        
        
        //game.physics.arcade.collide(this.ball, this.bricks);
        game.physics.arcade.collide(this.ball, this.bricks, this.removeBrick, null, this);
        
        
        // get input from the arrow keys
        var isLeftDown = game.input.keyboard.isDown(Phaser.Keyboard.LEFT);
        var isRightDown = game.input.keyboard.isDown(Phaser.Keyboard.RIGHT);
        
        // assign paddle position, check keyboard input (arrow keys are mutually exclusive) - check if mouse moved
        if (this.prevX !== game.input.x) {
            this.paddle.x = game.input.x;
        } else if (isRightDown && !isLeftDown) {
            this.paddle.x += this.paddleVelX * game.time.physicsElapsedMS;
        } else if (isLeftDown && !isRightDown) {
            this.paddle.x -= this.paddleVelX * game.time.physicsElapsedMS;
        }

        // assign current psotion
        this.prevX = game.input.x;

        // limit the movement of the paddlel to the sccreen bounds
        if (this.paddle.x - this.paddleHalf < 0) {
            this.paddle.x = 0 + this.paddleHalf;
        }

        if (this.paddle.x + this.paddleHalf > game.world.width) {
            this.paddle.x = game.world.width - this.paddleHalf;
        }
        
        // mode the ball according to the paddle's position
        if (this.ball.isShot === false) {
            this.ball.x = this.paddle.x;
        }
        
        // enable shoot via keyboard
        if (game.input.keyboard.isDown(Phaser.Keyboard.SPACEBAR)) {
            this.shootBall();
        }

        // animate the background
        this.bkg.tilePosition.y += 1;


    },
    
    resetPaddle: function () {
        
        // place the paddle in center of the screen
        this.paddle.x = game.world.centerX;
        // place the paddle a little higher than the bottom of the screen
        this.paddle.y = game.world.height - this.paddle.height;
        
        // place the ball
        this.ball.x = this.paddle.x;
        this.ball.y = this.paddle.y - this.paddle.height;
        this.ball.isShot = false;
        
        this.ball.body.velocity.set(0);
        
    }

};