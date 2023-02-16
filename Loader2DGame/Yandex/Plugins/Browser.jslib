mergeInto(LibraryManager.library, {
    //test
    Hello: function () {
        window.alert("Hello, world!");
        console.log("Hello World!");
        //MyGameInstance.SendMessage('MyGameObject', 'MyFunction', Arg);
    },
    CheckForRated: function(){
        ysdk.feedback.canReview()
            .then(({ value, reason }) => {
                if (value == false) {
                    myGameInstance.SendMessage('GameManager', 'FeedbackSent');
                }
            })
    },
    //Rate my game
    RateGame: function () {
        ysdk.feedback.canReview()
            .then(({ value, reason }) => {
                if (value) {
                    ysdk.feedback.requestReview()
                        .then(({ feedbackSent }) => {
                            console.log(feedbackSent);
                            myGameInstance.SendMessage('GameManager', 'FeedbackSent');
                        })
                } else {
                    console.log(reason)
                }
            })
    },
    //Save and load operation
    SaveExtern: function (date) {
        console.log('Start setting data');
        var dateString = UTF8ToString(date);
        var myobj = JSON.parse(dateString);
        player.setData(myobj);
        console.log('data is set');
    },
    LoadExtern: function () {
        console.log('Start loading data');
        if(player){
            player.getData().then(_date => {
            const myJSON = JSON.stringify(_date);
            myGameInstance.SendMessage('GameManager', 'LoadGame', myJSON);
            console.log('data is loaded');
        })};
    },

    UpdateLeaderboard: function (value) {
        ysdk.getLeaderboards()
            .then(lb => {
                // Без extraData
                lb.setLeaderboardScore('Items', value);
            });
    },
    AuthPlayer: function () {
        console.log("Try auth");
        AuthButton();
    },
    AskForPlayerAuth: function () {
        if (player.getMode() === 'lite') {
            console.log("Player is Guest");
            myGameInstance.SendMessage('MainMenu', 'GuestPlayer');
        } else {
            console.log("Player is normal");
            myGameInstance.SendMessage('MainMenu', 'NormalPlayer');
        }
    },
    GetLanguage: function(){
        var returnString = ysdk.environment.i18n.lang;
        var bufferSize = lengthBytesUTF8(returnString) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(returnString, buffer, bufferSize);
        console.log(buffer);
        return buffer;
    },
    ShowFullScreenAdv: function(){
        ysdk.adv.showFullscreenAdv({
            callbacks: {
                onClose: function(wasShown) {
                    console.log("Adv was shown");
                  // some action after close
                },
                onError: function(error) {
                  // some action on error
                }
            }
        })
    },
    InitRewardAdv: function(){
        ysdk.adv.showRewardedVideo({
            callbacks: {
                onOpen: () => {
                  console.log('Video ad open.');
                },
                onRewarded: () => {
                  console.log('Rewarded!');
                  myGameInstance.SendMessage('InGameUI', 'RewardAdvAction');
                },
                onClose: () => {
                  console.log('Video ad closed.');
                }, 
                onError: (e) => {
                  console.log('Error while open video ad:', e);
                }
            }
        })
    },
});