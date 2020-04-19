# olcPGEX_Particles

This extension is designed for use with the [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) by [Javidx9](https://github.com/OneLoneCoder). It allows you to easily use animated particles that utilize animated sprites that utilise either single-file spritesheets or multiple image files for each frame.

---

## Usage

To use the olcPGEX_Particles extension, it needs to be included in your application. This is done like so:

```cpp
#define OLC_PGEX_PARTICLES_APP
#include "olcPGEX_Particles.h"
```

### Default Particle with Default Animation

```cpp
// define particle in your PGE program
olc::Particles *particle;

bool OnUserCreate()
{
    // use default particle sprite, create, and move functions
    particle = new olc::Particles();
 
    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    olc::vf2d spawnPoint = { (float)GetMouseX(), (float)GetMouseY() };

    // spawn particles at spawnPoint when left mouse button is held down
    if(GetMouse(0).bHeld)
        particle->Spawn(spawnPoint);

    
    // move and draw the particles, if any have spawned
    particle->Draw(fElapsedTime);

    return true;
}
```

### Custom Particle with Default Animation

```cpp
// define particle in your PGE program
olc::Particles *particle;

bool OnUserCreate()
{
    // use custom particle sprite with default animation
    particle = new olc::Particles("path/to/your/particle.png");

    // set to use the StarBurst animation
    particle->SetCreateFunction(olc::ParticleAnimations::StarBurstCreate);
    particle->SetMoveFunction(olc::ParticleAnimations::StarBurstMove);

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    olc::vf2d spawnPoint = { (float)GetMouseX(), (float)GetMouseY() };

    // spawn particles at spawnPoint when left mouse button is held down
    if(GetMouse(0).bHeld)
        particle->Spawn(spawnPoint);

    
    // move and draw the particles, if any have spawned and are still alive
    particle->Draw(fElapsedTime);
}
```

### Custom Animations

Particle animations are controlled from 2 lambda functions. olcPGEX_Particles comes with 2 particle animations within the ``olc::ParticleAnimation`` namespace.
You may want create custom animations if the provided animations do not serve your purpose. You will need to write custom versions of the ``createFunc`` and ``moveFunc`` lambda functions. You can do this like so:

```cpp
bool OnUserCreate()
{
    // use custom particle sprite with default animation
    particle = new olc::Particles("path/to/your/particle.png");

    particle->SetCreateFunction([&](olc::Particle &p)
    {
        /* ... your particle creation code here ... */
    });
    
    particle->SetMoveFunction([&]olc::Particle &p, float fElapsedTime)
    {
        /* ... your particle movement code here ... */
    });
    
    return true;
}

```

Within the lambda functions ``p.lParticles`` is a ``std::list<sParticle>`` which is used to create and move each of the particles spawned. The following is the default particle animations.

### Particle Structure (for reference)

```cpp
// particle structure
struct sParticle {
    
    // position of this particle
    olc::vf2d pos = { 0.0f, 0.0f }; 
    
    // velocity of this particle
    olc::vf2d vel = { 0.0f, 0.0f };
    
    // x and y scale of this particle
    olc::vf2d scale = { 1.0f, 1.0f };
    
    // the orientation of the particle
    float angle = 0.0f;
    
    // the tint of this particle, useful for coloring and fading effects
    olc::Pixel tint = olc::WHITE;
    
    // arbitrary data, for use when persistent data is required for your custom animation
    float data[4];
    
    // remove flag, set to true to remove this particle (e.g. it's animation should be considered finished)
    bool remove = false;
};
```

### LinearCreate lambda function (for example)

```cpp
auto LinearCreate = [](olc::Particles &p)
{
    int particles = 25;
    for(int i = 0; i < particles; i++)
    {
        float speed = ((float)rand() / (float)RAND_MAX) * 200.0f;
        float fTheta = 2.0f * 3.14159f / particles;

        p.lParticles.push_back({
            p.GetPosition(), // pos
            { 180.0f * cosf(fTheta * i), 180.0f * sinf(fTheta * i)}, // vel
            { 0.1f, 0.1f }  // scale
        });
    }
};
```
### LinearMove lambda function (for example)

```cpp		
auto LinearMove = [](olc::Particles &p, float fElapsedTime)
{
    for(auto &particle : p.lParticles)
    {
        particle.pos += particle.vel * fElapsedTime;
        
        particle.scale.x += particle.scale.x * 2.0f * fElapsedTime;
        particle.scale.y += particle.scale.y * 2.0f * fElapsedTime;
        
        int temp = (255 - ((particle.scale.x / 0.9f) * 254));

        if(temp < 0)
            particle.tint = olc::Pixel(0,0,0,0);
        else
            particle.tint = olc::Pixel(temp, temp, temp, temp);

        if(particle.tint.a == 0)
            particle.remove = true;
    }

    p.lParticles.remove_if([&](olc::Particles::sParticle s) { return s.remove; });
};
```


---

## Contributions

Contributions are more than welcome. Please see [CONTRIBUTING.md](https://github.com/moros1138/olcPGEX_Particles/blob/dev/CONTRIBUTING.md) for more information.