

#include <SFML/Graphics.hpp>


#include <string>
#include <iostream>

#include <filesystem>


int main(int argc, char *argv[])
{

    std::string arg_filename;
    if(argc == 2)
    {
        arg_filename = std::string(argv[1]);
    }

    std::string image_filename = arg_filename;
    //image_filename = "test.png";


    // TODO: set WD to WD of image_filename
    // or store WD in std::string
    // set image_filename to be path without WD
    // (just filename not full path)



    // From SFML doc:
    // The supported image formats are bmp, png, tga, jpg, gif, psd, hdr and pic.
    // Some format options are not supported, like progressive jpeg.
    // If this function fails, the image is left unchanged.
    sf::Image image;
    bool image_load = false;
    if(!image.loadFromFile(image_filename))
    {
        std::cout << "Error: Could not load file " << image_filename << std::endl;
    }
    else
    {
        image_load = true;
    }
    sf::Vector2u image_size(image.getSize());

    sf::VideoMode videomode;
    if(image_load)
    {
        videomode = sf::VideoMode(image_size.x, image_size.y);
    }
    //sf::RenderWindow window(videomode, "Simple Image Viewer", sf::Style::Close);
    sf::RenderWindow window(videomode, "Simple Image Viewer");

    std::cout << "RenderWindow: " << window.getSize().x << " "
                                  << window.getSize().y << std::endl;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

/*
    sf::FloatRect rectangle(0, 0, image_size.x, image_size.y);
    sf::View view(rectangle);
    window.setSize(image_size);
    window.setView(view);
*/

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    std::cout << "Properties of Sprite:" << std::endl;
    std::cout << "Global bounds: " << sprite.getGlobalBounds().left << " "
                                   << sprite.getGlobalBounds().top << ", "
                                   << sprite.getGlobalBounds().width << " "
                                   << sprite.getGlobalBounds().height << std::endl;
    std::cout << "Local bounds: " << sprite.getLocalBounds().left << " "
                                  << sprite.getLocalBounds().top << ", "
                                  << sprite.getLocalBounds().width << " "
                                  << sprite.getLocalBounds().height << std::endl;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::Resized)
            {
                sf::FloatRect rectangle(0, 0, event.size.width, event.size.height);
                sf::View view(rectangle);
                window.setView(view);
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Left)
                {
                    std::cout << "Left" << std::endl;


                    std::string path = ".";
                    std::vector<std::string> filenames;
                    for(const auto &entry: std::filesystem::directory_iterator(path))
                    {
                        //std::cout << entry.path() << std::endl;
                        std::string path_string = entry.path();
                        //std::cout << path_string << std::endl;
                        if(path_string.rfind('/') != std::string::npos)
                        {
                            if((path_string.rfind('/') + 1) != std::string::npos)
                            {
                                path_string = path_string.substr(path_string.rfind('/') + 1);
                                std::cout << path_string << std::endl;
                            }
                            else
                            {
                                path_string = std::string("");
                            }
                        }
                        if(path_string.rfind('.') != std::string::npos)
                        {
                            if((path_string.rfind('.') + 1) != std::string::npos)
                            {
                                std::string extension = path_string.substr(path_string.rfind('.') + 1);
                                //std::cout << extension << std::endl;
                                if(
                                    (extension == std::string("bmp")) ||
                                    (extension == std::string("png")) ||
                                    (extension == std::string("tga")) ||
                                    (extension == std::string("jpg")) ||
                                    (extension == std::string("jpeg")) ||
                                    (extension == std::string("gif")) ||
                                    (extension == std::string("psd")) ||
                                    (extension == std::string("hdr")) ||
                                    (extension == std::string("pic"))
                                )
                                {
                                    filenames.push_back(path_string);
                                }
                            }
                        }
                    }

                    std::size_t ix = 0;
                    bool not_found = true;
                    std::size_t found_ix = 0;
                    for(; not_found && ix < filenames.size(); ++ ix)
                    {
                        if(filenames.at(ix) == image_filename)
                        {
                            if(ix == 0)
                            {
                                found_ix = filenames.size() - 1;
                                not_found = false;
                            }
                            else
                            {
                                found_ix = ix - 1;
                            }
                        }
                        else
                        {
                            std::cout << filenames.at(ix) << " is not " << image_filename << std::endl;
                        }
                    }

                    if(filenames.at(found_ix) != image_filename)
                    {
                        std::cout << "Loading: " << filenames.at(found_ix) << std::endl;
                        if(!image.loadFromFile(filenames.at(found_ix)))
                        {
                            std::cout << "Error: Could not load file " << image_filename << std::endl;
                        }
                        else
                        {
                            //image_load = true;
                            image_filename = filenames.at(found_ix);
                        }

                        texture.loadFromImage(image);
                        sprite.setTexture(texture);

                        sf::FloatRect rectangle(0, 0, image_size.x, image_size.y);
                        sf::View view(rectangle);
                        window.setSize(image_size);
                        window.setView(view);
                    }

                }
                else if(event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "Right" << std::endl;
                }
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();

        /*
        std::cout << "Properties of Window: " << std::endl;
        std::cout << "Size: " << window.getSize().x << " "
                              << window.getSize().y << std::endl;
        sf::View view(window.getView());
        std::cout << "View: " << view.getSize().x << " "
                              << view.getSize().y << std::endl;
        sf::FloatRect viewport(view.getViewport());
        std::cout << "Viewport: " << viewport.width << " "
                                  << viewport.height << std::endl;

        std::cout << "Properties of Sprite:" << std::endl;
        std::cout << "Global bounds: " << sprite.getGlobalBounds().left << " "
                                    << sprite.getGlobalBounds().top << ", "
                                    << sprite.getGlobalBounds().width << " "
                                    << sprite.getGlobalBounds().height << std::endl;
        std::cout << "Local bounds: " << sprite.getLocalBounds().left << " "
                                    << sprite.getLocalBounds().top << ", "
                                    << sprite.getLocalBounds().width << " "
                                    << sprite.getLocalBounds().height << std::endl;
        std::cout << "Sprite Scale: " << sprite.getScale().x << " "
                                      << sprite.getScale().y << std::endl;

        sf::sleep(sf::seconds(1.0f));
        */
    }

    return 0;
}