#pragma once
#include "PiratesEngine/Core/Input.h"
#include <stdlib.h>

namespace Pirates
{
	class  WindowsInput : public Input
	{
	public:

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int keycode) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual std::pair<float, float> GetMousePosImpl() override;

	};

}
