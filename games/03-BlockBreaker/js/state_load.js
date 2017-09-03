var StateLoad = {
    
    preload: function (){
    
        var progVoid = game.add.image(0, 0, 'imgProgVoid');
        progVoid.x = game.world.centerX - progVoid.width / 2;
        progVoid.y = game.world.centerY;
        
        var progFull = game.add.image(0, 0, 'imgProgFull');
        progFull.anchor.x = progVoid.anchor.x;
        progFull.x = progVoid.x;
        progFull.y = progVoid.y;
    
        game.load.setPreloadSprite(progFull);
      
        // from state_main:
        //---------------------
        // load paddle image
        game.load.image('imgPaddle', 'img/paddle.png');
        
        // load ball
        game.load.image('imgBall', 'img/ball.png');
                
        // load bricks
        game.load.image('imgBrickGreen', 'img/brick_green.png');
        game.load.image('imgBrickPurple', 'img/brick_purple.png');
        game.load.image('imgBrickRed', 'img/brick_red.png');
        game.load.image('imgBrickYellow', 'img/brick_yellow.png');
        
        // add background
        game.load.image('imgBkg', 'img/bg_blue.png');
        game.load.image('imgBlack', 'img/bg_black.png');
        
        // load audio
        game.load.audio('sfxHitBrick','snd/fx_hit_brick.wav');
        game.load.audio('sfxHitPaddle','snd/fx_hit_paddle.wav');
        game.load.audio('sfxLoseLife','snd/fx_lose_life.ogg');
        game.load.audio('bgmMusic','snd/bgm_electric_air.ogg');
        
        
        // from state_over
        //--------------------
        game.load.image('imgBkg', 'img/bg_blue.png')
        game.load.spritesheet('btnBack', 'img/btn_back.png', 190, 49);
        
        game.load.audio('sfxLose','snd/fx_lose.ogg');
        game.load.audio('sfxWin','snd/fx_win.ogg');
        
        game.load.audio('sfxFirework','snd/fx_firework.ogg');
        game.load.image('imgStar','img/star.png');
    },
    
    create: function () {
        
        game.state.start('StateIntro');
        
    }
};