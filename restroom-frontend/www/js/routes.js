angular.module('app.routes', [])

.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider
    
  

      .state('tabsController.page9', {
    url: '/restroom',
    views: {
      'tab1': {
        templateUrl: 'templates/page9.html',
        controller: 'page9Ctrl'
      }
    }
  })

  .state('tabsController.page3', {
    url: '/about',
    views: {
      'tab3': {
        templateUrl: 'templates/page3.html',
        controller: 'page3Ctrl'
      }
    }
  })

  .state('tabsController.page4', {
    url: '/lab',
    views: {
      'tab2': {
        templateUrl: 'templates/page4.html',
        controller: 'page4Ctrl'
      }
    }
  })

  .state('tabsController', {
    url: '/page1',
    templateUrl: 'templates/tabsController.html',
    abstract:true
  })

  .state('page5', {
    url: '/login',
    templateUrl: 'templates/page5.html',
    controller: 'page5Ctrl'
  })

  .state('page6', {
    url: '/signup',
    templateUrl: 'templates/page6.html',
    controller: 'page6Ctrl'
  })

$urlRouterProvider.otherwise('/page1/restroom')

  

});