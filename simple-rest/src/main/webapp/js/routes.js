angular.module('app.routes', [])

  .config(function($stateProvider, $urlRouterProvider) {

    // Ionic uses AngularUI Router which uses the concept of states
    // Learn more here: https://github.com/angular-ui/ui-router
    // Set up the various states which the app can be in.
    // Each state's controller can be found in controllers.js
    $stateProvider



      .state('tabsController.main', {
        url: '/restroom',
        views: {
          'tab1': {
            templateUrl: 'templates/main.html',
            controller: 'mainCtrl',
            controllerAs: 'main'
          }
        }
      })

      .state('tabsController.meetingroom', {
          url: '/meetingroom',
          views: {
            'tab2': {
                templateUrl: 'templates/meetingroom.html',
                controller: 'meetingroomCtrl',
                controllerAs: 'meetingroom'
            }
          }
      })

      .state('tabsController.about', {
        url: '/about',
        views: {
          'tab3': {
            templateUrl: 'templates/about.html',
            controller: 'aboutCtrl'
          }
        }
      })

      .state('tabsController', {
        url: '/page1',
        templateUrl: 'templates/tabsController.html',
        abstract:true
      })

      .state('login', {
        url: '/login',
        templateUrl: 'templates/login.html',
        controller: 'loginCtrl'
      })

      .state('page6', {
        url: '/signup',
        templateUrl: 'templates/page6.html',
        controller: 'page6Ctrl'
      })

      .state('lab', {
        url: '/lab',
        templateUrl: 'templates/lab.html',
        controller: 'labCtrl'
      })

      .state('settings', {
        url: '/settings',
        templateUrl: 'templates/settings.html',
        controller: 'settingsCtrl'
      })

      .state('breakfast', {
        url: '/breakfast',
        templateUrl: 'templates/breakfast.html',
        controller: 'breakfastCtrl',
        controllerAs: 'breakfast'
      });



    $urlRouterProvider.otherwise('/page1/restroom')

    // $httpProvider.interceptors.push('LoadingInterceptor');

  });
