/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <burakortakuz@gmail.com>          +#+  +:+       +#+        */
/*   Organizer: enver yılmaz                      +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:03:21 by bortakuz          #+#    #+#             */
/*   Updated: 2025/02/11 18:21:14 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP 250211L

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Texture2D.hpp>
#include <SpriteRenderer.hpp>

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.

class GameObject
{
protected:
// MODERN DEFINES :)
	constexpr static glm::vec2	defaultPosition = glm::vec2(0.0f, 0.0f);
	constexpr static glm::vec2	defaultSize 	= glm::vec2(1.0f, 1.0f);
	constexpr static glm::vec2	defaultVelocity = glm::vec2(0.0f, 0.0f);
	constexpr static float		defaultRotation = 0.0f;	
// VARIABLES
	glm::vec2   _position, _size, _velocity;
	glm::vec3   _color;
	float       _rotation;
	bool        _isSolid;   //__??__ TO-DO WTF
	bool        _destroyed; //__??__ TO-DO WTF
// RENDER STATE
	Texture2D   _sprite;
public:
// CONSTRUCTOR
	GameObject(
		glm::vec2 pos		= defaultPosition,
		glm::vec2 size		= defaultSize,
		Texture2D sprite	= Texture2D(),
		glm::vec3 color		= glm::vec3(1.0f),
		glm::vec2 velocity	= defaultVelocity
	);
	~GameObject();
// GETTERS
	glm::vec2	getPosition()	const;
	glm::vec2	getSize()		const;
	bool		isSolid()		const;
	bool		isDestroyed()	const;
// SETTERS
	void		setSolid(bool solid);
	void		setPosition(glm::vec2 pos);
// FUNCTIONS
	virtual void draw(SpriteRenderer &renderer);
};

#endif