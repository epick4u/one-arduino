angular.module('app.controllers', [])

.controller('mainCtrl', function($scope, mainSvc, $http) {
  console.log('Calling mainCtrl');
  $scope.floors = [{
    id: 13,
    restrooms: [{
      id: "13-1",
      startTime: null,
      occupied: false
    }, {
      id: "13-2",
      startTime: 1467210694777,
      occupied: true
    }, {
      id: "13-3",
      startTime: false,
      occupied: null
    }]
  }, {
    id: 12,
    restrooms: [{
      id: "12-1",
      startTime: null,
      occupied: false
    }, {
      id: "12-2",
      startTime: 1467210694777,
      occupied: true
    }, {
      id: "12-3",
      startTime: false,
      occupied: null
    }]
  }, {
    id: 11,
    restrooms: [{
      id: "12-1",
      startTime: null,
      occupied: false
    }, {
      id: "12-2",
      startTime: 1467210694777,
      occupied: true
    }, {
      id: "12-3",
      startTime: false,
      occupied: null
    }]
  }];
})

.controller('settingsCtrl', function($scope, mainSvc, $http) {
  console.log('Calling settingsCtrl');
  var restrooms = [];

  $http.get('http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/restroom')
    .success(function(data) {
      $scope.restrooms = data.sort(function(a, b) {
        if (a.id > b.id) {
          return 1;
        }
        if (a.id < b.id) {
          return -1;
        }
        return 0;
      });
    })
    .error(function(data, status, headers) {
      alert('Repos status ' + status + ' --- headers : ' + headers);
    });

  $scope.list = function() {
    console.log("Calling settingsCtrl#list");
    $http.get('http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/restroom')
      .success(function(data) {
        $scope.restrooms = data.filter(function(restroom) {
          if (!$scope.floor) {
            return true;
          }
          return restroom.id.split('-')[0] == $scope.floor;
        }).sort(function(a, b) {
          if (a.id > b.id) {
            return 1;
          }
          if (a.id < b.id) {
            return -1;
          }
          return 0;
        });
      })
      .error(function(data, status, headers) {
        alert('Repos status ' + status + ' --- headers : ' + headers);
      });
  }

  $scope.update = function(id, restroom) {
    console.log('Calling settingsCtrl#update');
    mainSvc.update(id, restroom);
    $scope.list();
  }
})

.controller('aboutCtrl', function($scope) {

})

.controller('labCtrl', function($scope) {
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
})

.controller('loginCtrl', function($scope) {
  $scope.user = {};
  $scope.login = function() {
    if ($scope.user.username === 'arduino.onelab' && $scope.user.password === 'Arduino12#$') {
      alert('Login success!');
    } else {
      alert('login failure!');
    }
  };
})

.controller('page6Ctrl', function($scope) {
});
