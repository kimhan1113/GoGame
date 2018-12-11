#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int cell_size = 40;
int cell_cnt = 19;

int main(void)
{
    RenderWindow window(VideoMode(cell_size*cell_cnt, cell_size*cell_cnt), "Go Game");
    Texture t1;t1.loadFromFile("black_stone.bmp");
    Texture t2;t2.loadFromFile("white_stone.bmp");
    t1.setSmooth(true);t2.setSmooth(true);
    Sprite bs(t1), ws(t2);

    Vertex line[] = 
    {
        Vertex(Vector2f(10,10)),
        Vertex(Vector2f(150,150))
    };
    line[0].color = Color::White;
    line[1].color = Color::White;
    int xx=0,yy=0;
    while(window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) window.close();
            if(e.type == Event::MouseButtonPressed)
            {
                printf("mouse button pressed!\n");
                if(e.mouseButton.button == Mouse::Left)
                {
                    xx=int(e.mouseButton.x/cell_size)*cell_size;
                    yy=int(e.mouseButton.y/cell_size)*cell_size;
                }
            }
        }
        window.clear(Color::Yellow);

        auto draw_board = [&]()
        {
            float half_cell = 1.0 * cell_size / 2;
            for(int y=0;y<cell_cnt;y++)
            {
                Vertex hline[] = {Vertex(Vector2f(half_cell, half_cell+y*cell_size)), Vertex(Vector2f(cell_size*cell_cnt-half_cell, half_cell+y*cell_size))};
                hline[0].color = Color::Black;
                hline[1].color = Color::Black;
                window.draw(hline, 2, Lines);
            }
            for(int x=0;x<cell_cnt;x++)
            {
                Vertex vline[] = {Vertex(Vector2f(half_cell+x*cell_size, half_cell)), Vertex(Vector2f(half_cell+x*cell_size, cell_size*cell_cnt-half_cell))};
                vline[0].color = Color::Black;
                vline[1].color = Color::Black;
                window.draw(vline,2,Lines);
            }
            float star_point_r = half_cell/5;
            CircleShape circle(star_point_r);
            circle.setFillColor(Color::Black);
            for(int y=0;y<3;y++)for(int x=0;x<3;x++)
            {
                circle.setPosition(half_cell+(3+6*x)*cell_size-star_point_r, half_cell+(3+6*y)*cell_size-star_point_r);
                window.draw(circle);
            }
        };
        draw_board();

        auto draw_stone = [&]()
        {
            CircleShape stone(1.0*cell_size/2);
            stone.setFillColor(Color::White);
            stone.setOutlineColor(Color::Black);
            stone.setOutlineThickness(-2); // inner grow

            stone.setPosition(xx, yy);
            //window.draw(stone);

            ws.setScale(1.0*cell_size/bs.getLocalBounds().width,1.0*cell_size/bs.getLocalBounds().height);
            ws.setPosition(xx,yy);
            window.draw(ws);

        };
        draw_stone();
        window.display();

    }

    return 0;
}
