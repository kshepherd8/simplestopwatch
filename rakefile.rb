PROJECT_ROOT  = File.expand_path( File.dirname(__FILE__) )

load 'vendor/ceedling/lib/rakefile.rb'

task :default => ['test:all']
