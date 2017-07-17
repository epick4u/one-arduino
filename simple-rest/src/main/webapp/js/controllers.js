var module = angular.module('app.controllers', []);

module.controller('breakfastCtrl', function($scope, BreakfastSvc, $log, $ionicPopup) {
  $log.info('Calling breakfastCtrl');
  var breakfast = this;

  breakfast.refresh = function() {

    breakfast.currentTime = new Date();

    BreakfastSvc.getRecipients()
      .then(function(response) {
        breakfast.recipients = response.data;
      });

    BreakfastSvc.getStatus()
      .then(function(response) {
        breakfast.status = response.data;
      });
  };

  breakfast.showConfirm = function() {
    var confirmPopup = $ionicPopup.confirm({
      title: '매진 되었나요?',
      template: '남은 수량과 다르게 매진된 상태라면 다른 동료가 헛걸음 하지 않게 매진 처리해주세요!'
    });

    confirmPopup.then(function(res) {
      if(res) {
        console.log('확인');
        BreakfastSvc.soldout()
          .then(function(response) {
            breakfast.status = response.data;
          });
      } else {
        console.log('취소');
      }
    });
  };


  breakfast.refresh();
});

module.controller('meetingroomCtrl', function(meetingroomSvc, FLOORS, $log) {
    $log.info('> MeetingRoomCtrl');
    var meetingroom = this;

    meetingroom.floors = FLOORS;

    meetingroom.list = function() {
        meetingroomSvc.list().
        then(function (result) {
          meetingroom.rooms = result;
        });
    }

    meetingroom.list();
});

module.controller('mainCtrl', function(MainSvc, FLOORS, $log) {
  $log.info('> MainCtrl');
  var main = this;

  main.floors = FLOORS;

  MainSvc.list().
    then(function (result) {
      $log.debug(result);
      main.restrooms = result.data;
    });

  main.list = function() {
    MainSvc.list().
      then(function (result) {
        $log.debug(result);
        main.restrooms = result.data;
      });
  }
});

module.controller('settingsCtrl', function($scope, SettingsSvc, $log) {
  $log.info('Calling settingsCtrl');

  SettingsSvc.list().
    then(function (data) {
      $scope.restrooms = data
  });

  $scope.list = function() {
    $log.info("Calling settingsCtrl#list");
    SettingsSvc.list($scope.floor).
      then(function (data) {
        $scope.restrooms = data
    });
  };

  $scope.update = function(id, restroom) {
    $log.info('Calling settingsCtrl#update');
    SettingsSvc.update(id, restroom);
    $scope.list();
  };
});

module.controller('aboutCtrl', function($scope) {

});

module.controller('page6Ctrl', function($scope) {

});

module.controller('labCtrl', function($scope) {
  var members = [
    {id: 1, name: '정승길', role: '랩장', img: '1466880064_malecostume.png'},
    {id: 2, name: '윤장한', role: '아두이노 개발', img: '1466880049_male3.png'},
    {id: 3, name: '김동현', role: '보드/센서 조립', img: '1466880069_supportmale.png'},
    {id: 4, name: '염동환', role: '훈수', img: '1466880076_matureman1.png'},
    {id: 5, name: '조성근', role: '관찰자', img: '1466880064_malecostume.png'},
    {id: 6, name: '정화수', role: '아무거나', img: '1466880049_male3.png'},
    {id: 7, name: '조한석', role: '부상', img: '1466880069_supportmale.png'},
    {id: 8, name: '남기선', role: '비선실세', img: '1466880049_male3.png'}
  ];
  $scope.members = members;
});

module.controller('loginCtrl', function($scope) {
  $scope.user = {};
  $scope.login = function() {
    if ($scope.user.username === 'arduino.onelab' && $scope.user.password === 'Arduino12#$') {
      alert('Login success!');
    } else {
      alert('login failure!');
    }
  };
});
