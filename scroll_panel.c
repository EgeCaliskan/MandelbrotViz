#include "raygui.h"
#include <stddef.h>
Rectangle panelRec = {1700, 200, 800, 1400};
Rectangle panelContentRec = {0,0, 200,0};
Vector2 panelScroll = {0,0};
Rectangle panelView = {0,0, 100, 100};
void panel_open(){
    GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &panelView);
}
void take_picture()
{

}
