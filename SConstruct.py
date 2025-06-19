env = Environment()

if env[CXX] in ['g++', 'clang++']:
    env.Append(CXXFLAGS=['-std=c++17']



env.VariantDir('build', '.', duplicate=0)
SConsignFile('build')

env.Program("build/main.cpp")
