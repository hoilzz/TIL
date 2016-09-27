# Getting started

## Installing the CLI

Grunt CLI 설치해야해.
sudo 사용해

> npm install -g grunt-cli

위 명령어는
- `grunt` command를 너의 시스템 path에 put할거야
- `grunt-cli` 설치하기는 grunt task runner를 설치하지 않는다.
- `grunt-cli`의 job은 간단하다 : `gruntfile`에 설치되어온 grunt version을 run

## How the CLI works
`grunt` 가 run 될 때 마다, node의 `require()` 시스템을 사용하는 설치된 grunt를 찾는다. 이것 때문에 너는 `grunt`를 run할 수 있다.

**starting working with Grunt**:
1 Change to the Project's root directory
2 Install project dependencies with `npm install`
3 Run Grunt with `grunt`

## Preparing a new Grunt Project

typical setup은 `package.json` 과 `Gruntfile`을 포함한다.

1 package.json : npm module로 배포된 *project의 metadata를 저장하기 위해 npm이 사용하는 파일*
2 Gruntfile : `Grunfile.js` or `Gruntfile.coffee` 이고 *환경설정 하거나 task를 정의* 하고 *Grunt plugin을 load* 하는데 사용된다.


## package.json
The `package.json` 파일은 프로젝트의 root directory에 속한다. 그리고 project source와 함께 커밋되어야한다. `package.json` 과 같은 동일한 폴더에서 npm install을 실행하는 것은 각 의존성 리스트의 올바른 버전을 설치한다.

`package.json` *파일을 생성하는 몇가지 방법*
- grunt-init template은  프로젝트-specific `package.json`을 자동으로 생성한다
- npm init은 기본 `package.json` 파일을 생성한다
- 아래 예제와 같이 시작하고 필요한만큼 확장해라.


  {
    "name": "my-project-name",
    "version": "0.1.0",
    "devDependencies": {
      "grunt": "~0.4.5",
      "grunt-contrib-jshint": "~0.10.0",
      "grunt-contrib-nodeunit": "~0.4.1",
      "grunt-contrib-uglify": "~0.5.0"
    }
  }


## Installing Grunt and gruntplugins

## The Gruntfile
`gruntfile.js` or `grunfilt.coffee` 은 root directory에 속한 valid JS or coffeescript다.

**component**
- "wrapper" function
- Project and task configuration
- Loading Grunt plugins and tasks
- Custom tasks

## An example Gruntfile
project metadata는 project의 package.json file Grunt config로 임포트된다. grunt-contrib-uglify plugin's uglify task는 소스 파일을 minify하고 metadata를 동적으로 이용하는 banner comment를 생성한다.????
grunt가 커맨드 라인에서 실행될 때, uglify task는 디폴트로 실행된다.

module.exports = function(grunt) {

  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    uglify: {
      options: {
        banner: '/* ! <%= pkg.name %> <%= grunt.template.today("yyyy-mm-dd") %> * /\n'
      },
      build: {
        src: 'src/<%= pkg.name %>.js',
        dest: 'build/<%= pkg.name %>.min.js'
      }
    }
  });

  // Load the plugin that provides the **"uglify" task.**
  grunt.loadNpmTasks('grunt-contrib-uglify');

  // Default task(s).
  grunt.registerTask('default', ['uglify']);

  };

- grunt 실행시, uglify task는 디폴트로 실행

grunt file을 쪼개서 보도록 하자.

## "wrapper" function

Every gruntfile (and gruntplugin) 이러한 basic format을 사용하고 grunt code는 이 function 내부에 명시되어야 한다

  module.exports = function(grunt) {
    // Do grunt-related things in here
  }

## Project and task configuration

Grunt task는 `Grunt.initConfig` method에 전달된 오브젝트에서 정의된 환경설정 data에 따라 다르다.

이 예제에서, `grunt.file.readJSON('package.json')`은 package.json에 저장된 JSON metadata를 import한다.
왜냐하면 `<% %>` template string은 config properties를 참조하기 때문에, configuration data (like filepath and filelist)는 반복을 줄이기 위해 명시된다.

환경설정 오브젝트 내부에 임시 데이터를 저장할 수 있다. 그리고 task가 필요한 프로퍼티와 충돌을 잃으키지 않는한 그것은 무시된다.
또한, 이것은 javascript이기 때문에, any valid JS를 사용할 수 있다.

대부분의 task와 같이, `grunt-contrib-uglify` plugin's uglify task는 동일한 이름의 프로퍼티에 명시된 환경설정이라고 예상한다. single source file을 single destination file로 minify하는 `build`라는 이름의 single uglify target과 함께 `banner` option이 명시되있다.

  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    uglify: {
      options: {
        banner: '/* ! <%= pkg.name %> <%= grunt.template.today("yyyy-mm-dd") %> * /\n'
      },
      build: {
        src: 'src/<%= pkg.name %>.js',
        dest: 'build/<%= pkg.name %>.min.js'
      }
    }
  });

- grunt.file.readJSON(package.json)은 package.json에 저장된 JSON metadata를 import
- `banner` option
- single source file을 minify하는 `build` function



## Loading Grunt Plugin and tasks
concatenation, minification and linting 과 같은 task를 사용하는 대다수는 grunt plugin에서 이용가능하다. plugin이 dependency로써 package.json에 명시되어있는 한, npm install을 통해 설치된다. 이것은 simple command와 함께 gruntfile 내부에서 활성화된다.

// Load the plugin that provides the "uglify" task.
grunt.loadNpmTasks('grunt-contrib-uglify');


- concatenation(연결), minification(감소), linting(?)은 grunt plugin에서 이용가능하다.
- package.json에 명시하여 npm install을 통해 설치
- grunt.loadNpmTasks('grunt-plugin-name')

## Custom tasks

default task를 정의하여 default로 1개 이상의 task를 환경설정하기 위해 Grunt를 환경설정할 수 있다. 다음 예제에서, task 명시 없이 커맨드 라인에서 `grunt를 실행하는 것`은 uglify task를 실행하는 것이다. `grunt uglify` or `grunt default`를 실행하는 것과 동일하다. task의 개수 (인자 없거나 있는)는 배열로 명시된다.

  // Default task(s).
  grunt.registerTask('default', ['uglify']);

만약 프로젝트가 Grunt plugin이 제공하지 않는 task를 필요하다면, gruntfile내부에 custom task를 정의할 수 있다.

  module.exports = function(grunt) {

    // A very basic default task.
    grunt.registerTask('default', 'Log some stuff.', function() {
      grunt.log.write('Logging some stuff...').ok();
    });
  }

Custom project-specific task는 Gruntfile에서 정의될 필요 없다. 외부 .js file에서 정의되고 grunt.loadTasks method를 통해 로드 될 수 있다. 

- default task 설정하기
- default로 uglify를 설정하면 `grunt uglify`와 `grunt default`와 같은 동작
- `grunt.registerTask('default', ['uglify'])`
