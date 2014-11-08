OUT=bin/emscripten/out.html

CXX=emcc
FILES=SDLTest\src\main.cpp ca2d\src\gltypes\GLTexture2D.cpp ca2d\src\gltypes\GLShaderProgram.cpp ca2d\src\gltypes\GLShader.cpp ca2d\src\gltypes\GLSharedHandle.cpp ca2d\src\gltypes\GLUniqueHandle.cpp
INCLUDE=-Ica2d/include -Idep/include -ISDLTest/include
CXXFLAGS=-s STB_IMAGE=1 -std=c++11 --embed-file dist@/

all: $(OUT)

clean:
	del $(subst /,\,$(OUT))

$(OUT):
	$(CXX) $(CXXFLAGS) $(FILES) $(INCLUDE) -o $(OUT)
	