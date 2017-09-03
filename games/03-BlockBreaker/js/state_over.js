var StateOver = {
  
    preload: function () {
        
        // moved to state_load.js
        
//        game.load.image('imgBkg', 'img/bg_blue.png')
//        game.load.spritesheet('btnBack', 'img/btn_back.png', 190, 49);
//        
//        game.load.audio('sfxLose','snd/fx_lose.ogg');
//        game.load.audio('sfxWin','snd/fx_win.ogg');
//        
//        game.load.audio('sfxFirework','snd/fx_firework.ogg');
//        game.load.image('imgStar','img/star.png');
    },
    
    create: function () {
        
        var points = game.points;
        var lives = game.lives;
        
        
        var w = game.world.width;
        var h = game.world.height;
                
        this.bkg = game.add.tileSprite(0, 0, w, h, 'imgBkg');
        
        var outFrame = 0;
        var overFrame = 1;
        var downFrame = 2;
        var margin = 30;
        
        var btnBack = game.add.button(0, 0, 'btnBack', this.goToIntro, this, overFrame, outFrame, downFrame);
        btnBack.anchor.set(.5, 1);
        btnBack.x = game.world.centerX;
        btnBack.y = game.world.height - margin;

        var txtOverConfig = {
            font: "40px sans-serif",
            fill: "#ffffff",
            align: "center"
        };
        
        var txtOver = game.add.text(0, 0, g_txtGameOver, txtOverConfig);
        txtOver.anchor.x = .5;
        txtOver.x = game.world.centerX;
        txtOver.y = margin * 2;

        if (lives > 0) {
            txtOver.fill = "#e0d700";
            txtOver.text = g_txtCongrats;
        }
        
        var txtPointsConfig = {
            font: "28px Overlock",
            fill: "#ffffff",
            align: "center"
        };
        
        var txtPoints = game.add.text(0, 0, points + g_txtPoints, txtPointsConfig);
        
        txtPoints.anchor.x = .5;
        txtPoints.x = game.world.centerX;
        txtPoints.y = game.world.centerY - margin;
        
        var sfxWinLose;
        if (lives > 0) {
            sfxWinLose = game.add.audio('sfxWin');
        } else {
            sfxWinLose= game.add.audio('sfxLose');
        }
        sfxWinLose.play();
        
        if (lives > 0) {
            this.sfxFirework = game.add.audio('sfxFirework');

            var maxParticles = 100;
            this.fireworks = game.add.emitter(0, 0, maxParticles);
            this.fireworks.makeParticles('imgStar');
            this.fireworks.gravity.y = 500;

            this.topTime = 1;
            this.timer = this.topTime;
        }
        
    },

    update: function () {
        
        if (game.input.keyboard.isDown(Phaser.Keyboard.SPACEBAR)) {
            this.goToIntro();
        }
        
        if (this.lives == 0) {
            return;
        }
        
        this.timer -= game.time.physicsElapsed;
        if (this.timer < 0) {
            this.timer = this.topTime;
            var randX = Math.random() * game.world.width;
            var randY = Math.random() * game.world.height;
            this.fireworks.x = randX;
            this.fireworks.y = randY;
            var duration = 800;
            var numStars = 10;
            this.fireworks.start(true, duration, null, numStars);
            this.sfxFirework.play();
        }
    },
    
    goToIntro: function () {
        
        game.state.start('StateIntro');
        
    },
    
    goToOver: function () {
        
        this.bgmMusic.stop();
        game.lives = this.lives;
        game.points = this.points;
        game.state.start('StateOver');
    }
    
};