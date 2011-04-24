$build_dir = 'build/'
$test_dir  = 'test/'
$src_dir   = 'app/'

$cc = 'cc'
$cf = '-Wall'
$src  = FileList[$src_dir + '*.c']
$objs = $src.map{ |s| s.sub('.c', '.o') }
$exec = 'splines'
$test_srcs = FileList[$test_dir + '*.c']
$test_objs = $test_srcs.map{ |s| s.sub('.c', '.o') }
$test_exec = 'test_splines'

rule '.o' => '.c' do |t|
  sh "#{$cc} #{$cf} #{t.source} -c -o #{t.name}"
end

directory $build_dir

file $exec => $objs do |t|
  sh "#{$cc} #{$cf} #{t.prerequisites.join(' ')} -o #{$build_dir + t.name}"
end

file $test_exec => ([$objs, $test_objs].flatten - [$src_dir + 'main.o']) do |t|
  sh "#{$cc} #{$cf} #{t.prerequisites.join(' ')} -o #{$build_dir + t.name}"
end

task :default => :build

desc "Builds the project"
task :build => [$build_dir, $exec] do |t|
end

desc "Removes all build products"
task :clean do |t|
  [$objs, $test_objs, $build_dir].flatten.each { |f| rm_rf f }
end

desc "Run all tests"
task :test => [$build_dir, $test_exec] do
  cd $build_dir
  sh "./#{$test_exec}"
end
