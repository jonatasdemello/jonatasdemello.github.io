Repos:
https://github.com/jonatasdemello

https://jonatasdemello.github.io/



$ gem install jekyll-import


# jonatasdemello.github.io
Software Developer

```
bundle install
bundle exec jekyll serve
bundle exec Jekyll serve --watch
bundle exec jekyll serve --force_polling
bundle exec jekyll serve --incremental
```

http://127.0.0.1:4000/


jekyll build - Builds the site and outputs a static site to a directory called _site.
jekyll serve - Does the same thing except it rebuilds any time you make a change and runs a local web server at http://localhost:4000.


Instructions

1. Install a full Ruby development environment 
	https://jekyllrb.com/docs/installation/
	
	Ruby version 2.4.0 or above, including all development headers (ruby version can be checked by running ruby -v)
	RubyGems (which you can check by running gem -v)
	GCC and Make (in case your system doesn’t have them installed, which you can check by running gcc -v,g++ -v and make -v in your system’s command line interface)

2. Install Jekyll and bundler gems
	gem install jekyll bundler
	
3. Create a new Jekyll site at ./myblog
	jekyll new myblog

4. Change into your new directory
	cd myblog
	
5. Build the site and make it available on a local server
	bundle exec jekyll serve
	
6. Now browse to http://localhost:4000


minima is the current default theme, and 
bundle show minima 
will show you where minima theme's files are stored on your computer.







cd C:\RubyDevKit

Auto-detect Ruby installations and add them to a configuration file for the next step.

ruby dk.rb init

Install the DevKit, binding it to your Ruby installation.

ruby dk.rb install


gem update && gem cleanup

bundle clean --force


jekyll build
jekyll build --watch
jekyll build -w
jekyll serve
jekyll serve --watch
jekyll serve -w


$ gem install jekyll
$ jekyll serve

gem install wdm

Alternatively, if you use a Gemfile, you can check if Jekyll runs on Windows and only then install the wdm Gem.

gem 'wdm', '~> 0.1.0' if Gem.win_platform?


May still not work
If you try to run jekyll build --watch or jekyll serve and the output directory already exists, Jekyll sometimes fails to build the site. If you encounter this problem, you can work around it by adding --force_polling to the end of your Jekyll command. See the discussion in twbs/bootstrap#14746 and jekyll/jekyll#2926 for more information.

Jekyll’s auto-regeneration feature sometimes does not work at all. jekyll/jekyll#2529 suggests it fails on 32-bit systems and there is no known workaround. As of Jekyll v2.4.0, if your system is affected by this problem, you need to manually disable the auto-regeneration feature when you want to serve a site using Jekyll by running jekyll serve --no-watch.



Download the zip file or clone the BlackDoc repo.

$ git clone git@github.com:karloespiritu/BlackDoc.git mysite
$ cd mysite

Make sure you have Ruby 2.2.5 or higher installed.

$ ruby --version
ruby 2.2.5

Install bundler and install dependencies.

$ gem install bundler
$ bundle install

Build and run your BlackDoc site.

$ jekyll serve




ERROR:  Error installing psych:
        The last version of psych (= 3.0.3) to support your Ruby & RubyGems was 3.0.3. 
		Try installing it with `gem install psych -v 3.0.3`
        psych requires Ruby version < 2.5, >= 2.2. The current ruby version is 2.5.0.
		



