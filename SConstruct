env = Environment(CPPPATH=['include', 'include/animators', 'include/objects', 'include/encoders', 'include/systems'], CXXFLAGS='-std=c++14 -g -O2 -fPIC', tools=['g++', 'gnulink'])

env.MergeFlags(['!pkg-config --cflags --libs cairo libavformat libavcodec libswresample libswscale libavutil'])

lib_objects = []
for file in Glob('./src/*.cpp') + Glob('./src/**/*.cpp'):
    obj = env.SharedObject(file)
    lib_objects.append(obj)

gathvl = env.SharedLibrary('gathvl', lib_objects, LIBS='')

env.Command(Dir('gathvl'), Dir('include'), 'cp -R $SOURCE $TARGET')

env.Program('vis_test', ['vis_test.cpp'] + lib_objects)

env.Alias('lib', [gathvl, Dir('gathvl/')])
