env = Environment()

env.VariantDir('build', '.', duplicate=0)
SConsignFile('build')

env.Program("build/main.cpp")
