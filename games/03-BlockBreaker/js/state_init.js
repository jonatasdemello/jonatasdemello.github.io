var StateInit = {
    
    preload: function (){
    
        game.load.image('imgProgVoid', 'img/progress_void.png');
        game.load.image('imgProgFull', 'img/progress_full.png');
    
    },
    
    create: function () {
        
        game.scale.pageAlignHorizontally = true;
        if (!game.device.desktop) {
            game.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
        }
        game.scale.refresh();
        game.state.start("StateLoad");
        
    }
};