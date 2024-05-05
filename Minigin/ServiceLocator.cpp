#include "ServiceLocator.h"

std::unique_ptr<dae::SoundSystem> ServiceLocator::_sm_instance = nullptr;
std::unique_ptr<dae::InputSystem> ServiceLocator::_im_instance = nullptr;