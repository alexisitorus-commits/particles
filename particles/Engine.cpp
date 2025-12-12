#include "Engine.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Engine::Engine()
{
	VideoMode vm = VideoMode::getDesktopMode();
	m_Window.create(vm, "Particle System", Style::Default);
}

void Engine::run()
{
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	Clock clock;
	while (m_Window.isOpen())
	{
		float dtAsSeconds = clock.restart().asSeconds();
		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			m_Window.close();

		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		{
			m_Window.close();
		}//escape key to close window


		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			Vector2i mousePos = Mouse::getPosition(m_Window);

			//5 particles per click
			for (int i = 0; i < 5; i++)
			{
				int numPoints = rand() % 26 + 25; //determines num of points for the particle 
				m_particles.emplace_back(m_Window, numPoints, mousePos);
			}
		}//left button clicked and constuct 5 particles at mouse position
	}
}

void Engine::update(float dtAsSeconds)
{
	//update all particles
	for (auto it = m_particles.begin(); it != m_particles.end();)
	{
		it->update(dtAsSeconds);

		if (it->getTTL() <= 0)
		{
			//erase returns next valid iterator
			it = m_particles.erase(it);
		}
		else
		{
			it++; //only increment if not erasing
		}
	}
}
void Engine::draw()
{
	m_Window.clear();
	//draw all particles
	for (const auto& particle : m_particles)
	{
		m_Window.draw(particle);
	}
	m_Window.display();
}