<?php

namespace App\Security;

use App\Entity\Device;
use App\Entity\DeviceSetting;
use App\Entity\Event;
use App\Entity\EventType;
use Symfony\Component\Security\Core\Authentication\Token\TokenInterface;
use Symfony\Component\Security\Core\Authorization\Voter\Voter;
use Symfony\Component\Security\Core\Security;

class DeviceOwnerVoter extends Voter
{
    private $security = null;

    public function __construct(Security $security)
    {
        $this->security = $security;
    }

    protected function supports($attribute, $subject): bool
    {
        $supportsAttribute = in_array($attribute, ['DEVICE_OWNER']);
        $supportsSubject = ($subject instanceof DeviceSetting) || ($subject instanceof EventType) || ($subject instanceof Event);

        return $supportsAttribute && $supportsSubject;
    }

    protected function voteOnAttribute($attribute, $subject, TokenInterface $token): bool
    {
        if( $subject instanceof Event )
            $device_item = $subject->getType();
        else
            $device_item = $subject;

        if(!$device_item)
            return false;

        $device = $token->getUser();

        if (!($device instanceof Device))
            return false;

        switch ($attribute) {
            case 'DEVICE_OWNER':
                if ($device->getName() == $device_item->getDevice()->getName() ) { return true; }
        }

        return false;
    }
}
