#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <mcpe.h>
#include <substrate.h>

#define LOG_TAG "blocks"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

static void (*Tile$initTiles_real)();
static void Tile$initTiles_hook(){
	Tile* tile;
	tile = new Tile(200, "cobblestone", &Material::stone);
	Tile::tiles[200] = tile
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void* Tile$initTiles = dlsym(RTLD_DEFAULT, "_ZN4Tile9initTiles");
	MSHookFunction((void*)Tile$initTiles, &Tile$initTiles_hook (void**), &Tile$initTiles_real);
	return JNI_VERSION_1_2;
}
