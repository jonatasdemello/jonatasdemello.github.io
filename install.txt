
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
		
