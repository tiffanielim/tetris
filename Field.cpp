//
// Created by Tiffanie Lim on 6/3/24.
//

#include "Field.h"
#include <vector>
#include <SFML/Graphics.hpp>

namespace te
{
    Field::Field(int ts)
    {
        tileSize = ts;

        Reset();

        int actualW = FIELD_WIDTH - 1;
        int actualH = FIELD_HEIGHT - 1;
        sf::Color gridColor = sf::Color(50, 50, 50, 128);

        std::vector<sf::Vertex> verts(actualW * 2 + actualH * 2);

        //create vertical lines
        for (int x = 0; x < actualW; x++)
        {
            verts[x * 2].position = sf::Vector2f((x+ 1)*ts, 0);
            verts[x * 2 + 1].position = sf::Vector2f((x + 1)*ts, FIELD_HEIGHT * ts);

            verts[x * 2].color = gridColor;
            verts[x * 2 + 1].color = gridColor;
        }

        //offset to begin drawing horizontal lines after verticals
        int off = actualW * 2;

        //create horizontal lines
        for (int y = 0; y < actualH; y++)
        {
            verts[off + y * 2].position = sf::Vector2f(0, (y+1)*ts);
            verts[off + y * 2 + 1].position = sf::Vector2f(FIELD_WIDTH * ts, (y + 1)*ts);

            verts[off + y * 2].color = gridColor;
            verts[off + y * 2 + 1].color = gridColor;
        }

        //initialize vertex buffer with grid lines
        grid.create(verts.size());
        grid.setUsage(sf::VertexBuffer::Usage::Static);
        grid.setPrimitiveType(sf::PrimitiveType::Lines);
        grid.update(verts.data(), verts.size(), 0);

    }

    void Field::SetPosition(int x, int y)
    {
        translateX = x;
        translateY = y;
        position = sf::RenderStates();
        position.transform.translate(x, y);
    }

    void Field::Spawn(Block::Type t)
    {
        //reset block to starting position
        blockOffset = 3;
        blockHeight = -4;
        currentRotation = 0;
        current = t;

        //remove first block in queue and push a new one
        if (queue.size() != 0) {
            queue.pop();
            queue.push(getRandomBlock());
        }
    }

    void Field::PlaceBlock()
    {
        //loop through block data and write it to the map
        std::vector<char> tiles = Block::GetBlockData(current, currentRotation);
        for (int i = 0; i < tiles.size(); i++) {
            int offsX = blockOffset + (i % 4);
            int offsY = blockHeight + (i / 4);

            //skip tiles outside map bounds
            if (offsX < 0 || offsX >= FIELD_WIDTH || offsY >= FIELD_HEIGHT)
                continue;

            if (tiles[i] != 0) {
                if (offsY < 0) {
                    Reset(); // game over aka the field will clear... so you can't lose lol
                    return;
                } else {
                    map[offsX][offsY] = current;
                }
            }
        }

        bool deletedRows[4] = { false };
        for (int y = blockHeight; y < std::min<int>(FIELD_HEIGHT,blockHeight + 4); y++)
        {
            bool full = true;

            //check if row is full
            for (int x = 0; x < FIELD_WIDTH; x++)
                if (map[x][y] == Block::Type::None)
                {
                    full = false;
                    break;
                }

            //if full, mark for deletion
            if (full)
            {
                deletedRows[y - blockHeight] = true;
                for (int x = 0; x < FIELD_WIDTH; x++)
                    map[x][y] = Block::Type::None;
            }
        }

        //collapse rows above cleared lines
        int moveOffset = 0;
        for (int y = FIELD_HEIGHT; y >= 0; y--) {
            //skip deleted rows
            if (y >= blockHeight && y < blockHeight + 4)
                if (deletedRows[y - blockHeight]) {
                    moveOffset++;
                    continue;
                }

            //skip if no rows need moving
            if (moveOffset == 0)
                continue;

            //move current row down
            for (int x = 0; x < FIELD_WIDTH; x++)
                map[x][y + moveOffset] = map[x][y];
        }
    }

    void Field::Reset()
    {
        //clear board
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            for (int y = 0; y < FIELD_HEIGHT; y++)
            {
                map[x][y] = Block::Type::None;
            }
        }
        Spawn(getRandomBlock()); //spawn initial block and fill queue

        for (int i = 0; i < QUEUE_SIZE; i++)
        {
            queue.push(getRandomBlock());
        }
    }

    void Field::OnEvent(sf::Event e)
    {
        if (e.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key kc = e.key.code;

            if (kc == sf::Keyboard::Up || kc == sf::Keyboard::W) {
                currentRotation++;
                //undo rotation if out of bounds
                if (checkLeftBounds() || checkRightBounds())
                    currentRotation--;
            }
            else if (kc == sf::Keyboard::Left || kc == sf::Keyboard::A) {
                blockOffset = std::max<int>(blockOffset - 1, -2);
                if (checkLeftBounds())
                    blockOffset++;
            }
            else if (kc == sf::Keyboard::Right || kc == sf::Keyboard::D) {
                blockOffset = std::min<int>(blockOffset + 1, FIELD_WIDTH - 1);
                if (checkRightBounds())
                    blockOffset--;
            }
        }
    }
    void Field::OnUpdate()
    {
        std::vector<sf::Vector2i> tiles = Block::GetCollisionTiles(current, currentRotation);

        //check if any part of block should be placed
        for (int i = 0; i < tiles.size(); i++) {
            int offsX = tiles[i].x + blockOffset;
            int offsY = tiles[i].y + blockHeight;

            bool shouldPlace = false;

            if (offsY == FIELD_HEIGHT) // bottom bounds
                shouldPlace = true;

            //check collision with placed tiles
            if (offsX >= 0 && offsX < FIELD_WIDTH && offsY >= 0 && offsY < FIELD_HEIGHT)
                if (map[offsX][offsY] != Block::Type::None)
                    shouldPlace = true;

            //if it collides, place block and spawn next
            if (shouldPlace) {
                PlaceBlock();
                Spawn(queue.front());
                break;
            }
        }

        //move block down by one row
        blockHeight++;
    }
    void Field::Render(sf::RenderTarget & wnd)
    {
        //draw falling block
        Block::Render(wnd, current, translateX+tileSize*blockOffset, translateY+tileSize*blockHeight, tileSize, currentRotation);

        //draw placed tiles
        sf::RectangleShape tile;
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        for (int x = 0; x < FIELD_WIDTH; x++) {
            for (int y = 0; y < FIELD_HEIGHT; y++) {
                tile.setPosition(x*tileSize, y*tileSize);
                tile.setFillColor(Block::GetColor(map[x][y]));
                wnd.draw(tile, position);
            }
        }

        //draw grid lines
        wnd.draw(grid, position);
    }

    bool Field::checkLeftBounds()
    {
        std::vector<char> data = Block::GetBlockData(current, currentRotation);
        for (int i = 0; i < data.size(); i++) {
            int offsX = i%4 + blockOffset;
            int offsY = i/4 + blockHeight;

            if (data[i] == 0) // if it's not actually an occupied tile, skip it
                continue;

            // else, check if it is out of left bounds
            if (offsX < 0)
                return true;

            // or if there is already tile placed there
            if (offsX >= 0 && offsX < FIELD_WIDTH && offsY >= 0 && offsY < FIELD_HEIGHT)
                if (map[offsX][offsY] != Block::Type::None)
                    return true;
        }
        return false;
    }

    bool Field::checkRightBounds()
    {
        std::vector<char> data = Block::GetBlockData(current, currentRotation);
        for (int i = 0; i < data.size(); i++) {
            int offsX = i % 4 + blockOffset;
            int offsY = i / 4 + blockHeight;

            if (data[i] == 0) // if it's not actually occupied tile, skip it
                continue;

            // else, check if it is out of right bounds
            if (offsX >= FIELD_WIDTH)
                return true;

            // or if there is already tile placed there
            if (offsX >= 0 && offsX < FIELD_WIDTH && offsY >= 0 && offsY < FIELD_HEIGHT)
                if (map[offsX][offsY] != Block::Type::None)
                    return true;
        }

        return false;
    }
}