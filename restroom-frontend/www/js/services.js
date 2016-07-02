const baseUrl = "http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/restroom";

angular.module('app.services', [])

.service('SettingsSvc', function($http) {
  var mainSvc = this;

  mainSvc.update = function(id, restroom) {
    console.log('>> Calling mainSvc#update');

    var action = restroom.occupied ? 'in' : 'out';
    var url = baseUrl + '/' + id + '/' + action;
    console.log(url);

    $http.get(url).success(function(data) {
    }).error(function(data, status, headers) {
      alert('Repos status ' + status + ' --- headers : ' + headers);
    });
  };

  // TODO Doesn' work because of async
  mainSvc.list = function(floor) {
    console.log('>> Calling mainSvc#list');

    return $http.get(baseUrl)
      .then(function(result) {
        return result.data.filter(function(restroom) {
          if (!floor) {
            return true;
          }
          return restroom.id.split('-')[0] == floor;
        }).sort(function(a, b) {
          if (a.id > b.id) {
            return 1;
          }
          if (a.id < b.id) {
            return -1;
          }
          return 0;
        });
      });
  };

});
