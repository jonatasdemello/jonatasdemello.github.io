var StateIntro = {
    
    preload: function () {
        
        game.load.image('imgBkg','img/bg_blue.png');
        game.load.image('imgLogo','img/logo_game.png');
        
        game.load.spritesheet('btnStart','img/btn_start.png', 190, 49);
    },
    
    create: function () {
  
        var w = game.world.width;
        var h = game.world.height;
                
        this.bkg = game.add.tileSprite(0, 0, w, h, 'imgBkg');
                
        var margintTop = 30;
        var logo = game.add.image(0, 0, 'imgLogo');
        logo.anchor.x = .5;
        logo.x = game.world.centerX;
        logo.y = margintTop;
        
        var outFrame = 0;
        var overFrame = 1;
        var downFrame = 2;
        
        var btnStart = game.add.button(0, 0, 'btnStart', this.goToMain, this, overFrame, outFrame, downFrame);
        btnStart.anchor.x = .5;
        btnStart.x = game.world.centerX;
        btnStart.y = game.world.centerY;
        
    },
    
    update: function () {
        
        if (game.input.keyboard.isDown(Phaser.Keyboard.SPACEBAR)) {
            this.goToMain();
        }
        // animate the background
        this.bkg.tilePosition.y += 1;
    },
    
    goToMain: function () {
        
        game.state.start('StateMain');
        
    }
    
};