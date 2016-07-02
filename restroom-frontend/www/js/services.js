const baseUrl = "http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/restroom";
var restroomArray = [{
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

angular.module('app.services', [])

.service('MainSvc', function($http, $log) {
  var svc = this;

  svc.list = function() {
    $log.info('>> MainSvc#list');

    return $http.get(baseUrl)
      .then(function(result) {
        $log.debug(result);
        result.data = restroomArray;
        // Transfer the given object instead of faking data
        return result;
      });
  };

})

.service('SettingsSvc', function($http, $log) {
  var mainSvc = this;

  mainSvc.update = function(id, restroom) {
    $log.info('>> SettingsSvc#update');

    var action = restroom.occupied ? 'in' : 'out';
    var url = baseUrl + '/' + id + '/' + action;

    $http.get(url).success(function(data) {
    }).error(function(data, status, headers) {
      alert('Repos status ' + status + ' --- headers : ' + headers);
    });
  };

  // TODO Doesn' work because of async
  mainSvc.list = function(floor) {
    $log.info('>> SettingsSvcc#list');

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

/*
.factory('LoadingInterceptor', function (LoadingService, $log) {
    $log.debug('LoadingInterceptor');
    var loadingInterceptor = {
        request: function (request) {
            LoadingService.setLoading(true);
            return request;
        },
        response: function (response) {
            LoadingService.setLoading(false);
            return response;
        }
    };
    return loadingInterceptor;
})

.service('LoadingService', function ($rootScope, $log) {
    $log.debug('LoadingService');
    var service = this;

    service.setLoading = function(loading) {
        $rootScope.loading = true;
    };
});
*/
