//const baseUrl = "http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080";
const baseUrl = "http://onemakers.com";

var module = angular.module('app.services', []);

module.service('BreakfastSvc', function($http, $log) {
  var svc = this;
  var breakfastUrl = baseUrl + '/breakfast';

  svc.getRecipients = function() {
    $log.info('>> BreakfastSvc#getRecipients');
    return $http.get(breakfastUrl + '/recipient');
  };

  svc.getStatus = function() {
    $log.info('>> BreakfastSvc#getStatus');
    return $http.get(breakfastUrl + '/status');
  };

  svc.soldout = function() {
    $log.info('>> BreakfastSvc#soldout');
    return $http.get(breakfastUrl + '/soldout');
  };
});

module.service('MainSvc', function($http, $log) {
  var svc = this;

  svc.list = function() {
    $log.info('>> MainSvc#list');

    return $http.get(baseUrl + '/restroom')
      .then(function(result) {
        $log.debug(result);
        // result.data = restroomArray;
        // Transfer the given object instead of faking data
        return result;
      });
  };

});

module.service('meetingroomSvc', function($http, $log) {
    var svc = this;

    svc.list = function() {
        $log.info('>> meetingroomSvc#list');

        return $http.get(baseUrl + '/meetingroom')
            .then(function(result) {
                $log.debug(result);
                //result.data = restroomArray;
                return result.data;
            });
    };
});

module.service('SettingsSvc', function($http, $log) {
  var mainSvc = this;

  mainSvc.update = function(id, restroom) {
    $log.info('>> SettingsSvc#update');

    var action = restroom.occupied ? 'in' : 'out';
    var url = baseUrl + '/restroom/' + id + '/' + action;

    $http.get(url).success(function(data) {
    }).error(function(data, status, headers) {
      alert('Repos status ' + status + ' --- headers : ' + headers);
    });
  };

  // TODO Doesn' work because of async
  mainSvc.list = function(floor) {
    $log.info('>> SettingsSvcc#list');

    return $http.get(baseUrl + '/restroom')
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

module.value('FLOORS', [13, 12, 11]);
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
