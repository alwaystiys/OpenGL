#include "Common/window_backend.h"
#include "AppTest.h"
#include "SimpleTriangle.h"
#include "ShaderTriangle.h"
#include "TextureTest.h"
#include "TransformTest.h"
#include "CoordinateTest.h"
#include "CameraTest.h"
#include "LightTest.h"
#include "LightingMaps.h"
#include "LightCaster.h"

int main(int argc, char** argv) {
    if(!GLFWBackendCreateWindow("TestDemo", 800, 600, true)) {
        return 1;
    }
    //AppTest* app = new AppTest();
    //AppTriangle* app = new AppTriangle();
    //AppIndexTriangle *app = new AppIndexTriangle();
    //ShaderTriangle *app = new ShaderTriangle();
    //UniformTriangle *app = new UniformTriangle();
    //Uniform2Triangle *app = new Uniform2Triangle();
    //SimpleTexture *app = new SimpleTexture();
    //MultipleTexture *app = new MultipleTexture();
    //TransformTest::MultipleTexture *app = new TransformTest::MultipleTexture();
    //CoordinateTest::MultipleTexture *app = new CoordinateTest::MultipleTexture();
    //CoordinateTest::CubeTest *app = new CoordinateTest::CubeTest();
    //CoordinateTest::MutitudeCubeTest *app = new CoordinateTest::MutitudeCubeTest();
    //CameraTest::MutitudeCubeTest *app = new CameraTest::MutitudeCubeTest();
    //CameraTest::FPSTest *app = new CameraTest::FPSTest();
    //CameraTest::FPS2Test *app = new CameraTest::FPS2Test();
    //LightTest::FPS2Test *app = new LightTest::FPS2Test();
    //LightTest::BasicLightTest *app = new LightTest::BasicLightTest();
    //LightTest::MaterialTest *app = new LightTest::MaterialTest();
    //LightMapsTest::MaterialTest *app = new LightMapsTest::MaterialTest();
    //LightCasterTest::LightCaster *app = new LightCasterTest::LightCaster();
    //LightCasterTest::PointLightsTest *app = new LightCasterTest::PointLightsTest();
    //LightCasterTest::SpotlightTest *app = new LightCasterTest::SpotlightTest();
    //LightCasterTest::BetterSpotlightTest *app = new LightCasterTest::BetterSpotlightTest();
    LightCasterTest::MultiplelightTest *app = new LightCasterTest::MultiplelightTest();
    if(!app->Init()) {
        system("pause");
        return 1;
    }
    GLFWBackendRun(app);
    delete app;
    GLFWBackenShutDown();
    system("pause");
    return 0;
}
