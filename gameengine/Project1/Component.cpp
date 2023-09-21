#include "Component.h"

void GameEngine::Component::setEnabled(bool enabled)
{
	if (!m_enabled && enabled == true)
	{
		onEnable();
	}
	else if (m_enabled && !enabled == false)
	{
		onDisable();
	}

	m_enabled = enabled;
}
