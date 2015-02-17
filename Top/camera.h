#ifndef __CAMERA_INCLUDED_H__
#define __CAMERA_INCLUDED_H__

class PlayerView
{
    public:
        float atVertex[3];
        float toVertex[3];
        float upVector[3];
        float angle;

        PlayerView();
        void view();
        void updateCameraCoord(float dir);
};
PlayerView::PlayerView()
{
     atVertex[0] = -56.0, atVertex[1] = -36.0; atVertex[2] = 0.4;
     toVertex[0] = 0.0; toVertex[1] = 0.4; toVertex[2] = 0.4;
     upVector[0] = 0.0; upVector[1] = 0.0; upVector[2] = 1.0;
     angle = 0.0;
}
void PlayerView::view()
{
    if(atVertex[0] >= 60 || atVertex[0] <= -60)
    {
        if(atVertex[0] < 0)
            atVertex[0] = -60.0;
        else
            atVertex[0] = 60.0;
	}
    if(atVertex[1] >= 38 || atVertex[1] <= -38)
    {
        if(atVertex[1] > 0)
            atVertex[1] = 38.0;
        else
            atVertex[1] = -38.0;
	}
    gluLookAt(atVertex[0], atVertex[1], atVertex[2],
              atVertex[0] + toVertex[0], atVertex[1] + toVertex[1], toVertex[2],
              upVector[0], upVector[1], upVector[2]);
}
void PlayerView::updateCameraCoord(float dir)
{
    atVertex[0] += dir * toVertex[0] * 0.1;
    atVertex[1] += dir * toVertex[1] * 0.1;
}
    
class Heli
{
    public:
        float atVertex[3];
        float toVertex[3];
        float upVector[3];
        float angle;

        Heli();
        void view();
        void updateCameraCoord(float dir);
};
Heli::Heli()
{
     atVertex[0] = -56.0, atVertex[1] = -36.0; atVertex[2] = 0.4;
     toVertex[0] = 0.0; toVertex[1] = 0.4; toVertex[2] = 0.4;
     upVector[0] = 0.0; upVector[1] = 0.0; upVector[2] = 1.0;
     angle = 0.0;
}
void Heli::view()
{
    if(atVertex[0] >= 60 || atVertex[0] <= -60)
    {
        if(atVertex[0] < 0)
            atVertex[0] = -60.0;
        else
            atVertex[0] = 60.0;
	}
    if(atVertex[1] >= 38 || atVertex[1] <= -38)
    {
        if(atVertex[1] > 0)
            atVertex[1] = 38.0;
        else
            atVertex[1] = -38.0;
	}
    gluLookAt(atVertex[0], atVertex[1], atVertex[2],
              atVertex[0] + toVertex[0], atVertex[1] + toVertex[1], atVertex[2] + toVertex[2],
              upVector[0], upVector[1], upVector[2]);
}
void Heli::updateCameraCoord(float dir)
{
    atVertex[0] += dir * toVertex[0] * 0.1;
    atVertex[1] += dir * toVertex[1] * 0.1;
}


#endif

