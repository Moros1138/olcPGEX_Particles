#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_PARTICLES_APP
#include "olcPGEX_Particles.h"

class PGE_ParticleExample : public olc::PixelGameEngine
{
public:
	PGE_ParticleExample()
	{
		sAppName = "ParticleExample";
	} 

public:
	
	bool OnUserCreate() override
	{
		// use default particle sprite, create, and move functions
		particle = new olc::Particles();
		
		// Using alternative animations
		// particle->SetCreateFunction(olc::ParticleAnimations::StarBurstCreate);
		// particle->SetMoveFunction(olc::ParticleAnimations::StarBurstMove);
		
		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override
	{
		// get the mouse position (as floats)
		spawnPoint = { (float)GetMouseX(), (float)GetMouseY() };

		// spawn a particles when mouse button is held
		if(GetMouse(0).bHeld)
			particle->Spawn(spawnPoint);
			
		// draw particles
		particle->Draw(fElapsedTime);

		return !GetKey(olc::ESCAPE).bPressed;
	}

private:
	olc::vf2d spawnPoint;
	olc::Particles *particle;
};

int main()
{
	PGE_ParticleExample app;
	if(app.Construct(640, 480, 1, 1))
		app.Start();

	return 0;
}
