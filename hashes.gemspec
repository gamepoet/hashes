Gem::Specification.new do |s|
  s.name        = 'hashes'
  s.version     = '0.0.1'
  s.summary     = 'Non-cryptographic hash functions.'
  s.description = 'Implementations of Lookup3 and Murmur3 hash functions.'
  s.authors     = ['Ben Scott']
  s.email       = ['gamepoet@gmail.com']
  s.homepage    = 'http://github.com/gamepoet/hashes'
  s.files       = Dir.glob('lib/**/*.rb') +
                  Dir.glob('ext/**/*.{c,h,rb}')
  s.extensions  = ['ext/hashes/extconf.rb']
end
