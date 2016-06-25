angular.module('app.controllers', [])

.controller('page9Ctrl', function($scope) {

})

.controller('page3Ctrl', function($scope) {

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

.controller('page5Ctrl', function($scope) {

})

.controller('page6Ctrl', function($scope) {

})
