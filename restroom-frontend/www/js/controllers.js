var module = angular.module('app.controllers', []);

module.controller('breakfastCtrl', function(BreakfastSvc, $log) {
  $log.info('Calling breakfastCtrl');
  var breakfast = this;

  breakfast.recipients = [];
  for (var i = 0; i < 10; i++) {
    breakfast.recipients.push({id: i, cardId: i, name: 'Dale Seo', team: 'PF1'});
  }
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
    {id: 5, name: '최은봉', role: '퍼실리테이터', img: '1466880054_female1.png'},
    {id: 6, name: '조성근', role: '관찰자', img: '1466880064_malecostume.png'},
    {id: 7, name: '서대영', role: '아무거나', img: '1466880049_male3.png'},
    {id: 8, name: '조한석', role: '부상', img: '1466880069_supportmale.png'}
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
