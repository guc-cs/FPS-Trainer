CC = gcc
CFLAGS = -fno-stack-protector -lglut -lGL -lGLU -lm -lstdc++

TARGET = FPSTrainer

all: $(TARGET)

$(TARGET):
	$(CC) -o $(TARGET) Camera.cpp FPCam.cpp Md2Model.cpp SphereBarrier.cpp TextureProcessor.cpp CollisionEngine.cpp GUI.cpp PhysicsEngine.cpp Terrain.cpp $(CFLAGS)

clean:
	$(RM) $(TARGET)	
