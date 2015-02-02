from distutils.core import setup, Extension
 
module1 = Extension('pyiface',
                    define_macros = [('MAJOR_VERSION', '0'),
                                     ('MINOR_VERSION', '1')], 
                    sources = ['src/pyiface.c', 'src/iface.c'])
 
setup(name = 'pyIface',
      version = '0.1',
      description = 'It is an interface to get NIC information',
      author = 'Alfredo Miranda',
      author_email = 'alfredocdmiranda@gmail.com',
      url = 'https://github.com/alfredocdmiranda/pyIface',
      license='MIT',
      ext_modules = [module1])
