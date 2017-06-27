var BunnyDefender = {};

BunnyDefender.Boot = function(game) {}; // game = same as Index 

BunnyDefender.Boot.prototype = {
    
    preload: function() {
        this.load.image('preloaderBar','images/loader_bar.png');
        this.load.image('titleimage','images/TitleImage.png')
    },

    create: function() {
        this.input.maxPointers = 1;
        this.stage.disableVisibilityChange = false; // pause game on tab change
        this.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
        this.scale.minWidth = 270;
        this.scale.minHeight = 480;
        this.scale.pageAlignHorizontally = true;
        this.scale.pageAlignVertically = true;
        this.stage.forcePortrait = true;  // force portrait mode
        this.scale.setScreenSize(true);  // true will force screen resize no matter what

        this.input.addPointer();
        this.stage.backgroundColor = '#171642';
        
        this.state.start('Preloader');
    }
};