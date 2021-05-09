#pragma once
#include "gameObject.h"

class Brick final : public GameObject {

	bool m_IsSolid;

public:
	Brick(const glm::vec2& position,
	      const glm::vec2& size, const
	      std::string& texture,
	      const std::string& shader,
	      const glm::vec4& color,
	      bool isSolid = false);
	~Brick() override;

	inline bool isSolid() const { return m_IsSolid; }
};
