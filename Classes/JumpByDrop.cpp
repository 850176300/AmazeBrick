#include "JumpByDrop.h"

JumpByDrop::JumpByDrop(){
    
}

JumpByDrop* JumpByDrop::create(float duration, const Vec2& position, float height, int jumps)
{
    
    JumpByDrop *JumpByDrop = new class JumpByDrop();
    JumpByDrop->initWithDuration(duration, position, height, jumps);
    JumpByDrop->autorelease();

    return JumpByDrop;
}

bool JumpByDrop::initWithDuration(float duration, const Vec2& position, float height, int jumps)
{
    CCASSERT(jumps>=0, "Number of jumps must be >= 0");
    
    if ( jumps>=0)
    {
        _duration = duration;
        
        // prevent division by 0
        // This comparison could be in step:, but it might decrease the performance
        // by 3% in heavy based action games.
        if (_duration == 0)
        {
            _duration = FLT_EPSILON;
        }
        
        _elapsed = 0;
        _firstTick = true;
        
        _delta = position;
        _height = height;
        _jumps = jumps;

        return true;
    }

    return false;
}

JumpByDrop* JumpByDrop::clone() const
{
	// no copy constructor
	JumpByDrop* a = new JumpByDrop();
	a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

bool JumpByDrop::isDone() const
{
     log("JumpByDrop::update(float t)");
    return false;//_elapsed >= _duration;
}

void JumpByDrop::step(float dt)
{
    if (_firstTick)
    {
        _firstTick = false;
        _elapsed = 0;
    }
    else
    {
        _elapsed += dt;
    }
    
    this->update(MAX (0,                                  // needed for rewind. elapsed could be negative
                      MIN(1.0, _elapsed /
                          MAX(_duration, FLT_EPSILON)   // division by 0
                          )
                      )
                 );
}

void JumpByDrop::setAmplitudeRate(float amp)
{
    CC_UNUSED_PARAM(amp);
    // Abstract class needs implementation
    CCASSERT(0, "");
}

float JumpByDrop::getAmplitudeRate()
{
    // Abstract class needs implementation
    CCASSERT(0, "");
    
    return 0;
}

void JumpByDrop::startWithTarget(Node *target)
{
    FiniteTimeAction::startWithTarget(target);
    _elapsed = 0.0f;
    _firstTick = true;
    _previousPos = _startPosition = target->getPosition();
}

void JumpByDrop::update(float t) 
{
    log("the t delta time is %.2f", t);
    // parabolic jump (since v0.8.2)
    if (_target)
    {
        float frac = fmodf( t * _jumps, 1.0f );
        float y = _height * 4 *  frac * (1 - frac);
        y += _delta.y * t;

        float x = _delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();

        Vec2 diff = currentPos - _previousPos;
        _startPosition = diff + _startPosition;

        Vec2 newPos = _startPosition + Vec2(x,y);
        _target->setPosition(newPos);

        _previousPos = newPos;
#else
        _target->setPosition(_startPosition + Vec2(x,y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

JumpByDrop* JumpByDrop::reverse() const
{
    return JumpByDrop::create(_duration, Vec2(-_delta.x, -_delta.y),
        _height, _jumps);
}