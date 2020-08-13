<?php
// api/src/Doctrine/CurrentUserExtension.php

namespace App\Doctrine;

use ApiPlatform\Core\Bridge\Doctrine\Orm\Extension\QueryCollectionExtensionInterface;
use ApiPlatform\Core\Bridge\Doctrine\Orm\Extension\QueryItemExtensionInterface;
use ApiPlatform\Core\Bridge\Doctrine\Orm\Util\QueryNameGeneratorInterface;
use App\Entity\DeviceSetting;
use App\Entity\EventType;
use App\Entity\Event;
use Doctrine\ORM\QueryBuilder;
use Symfony\Component\Security\Core\Security;

final class CurrentDeviceExtension implements QueryCollectionExtensionInterface, QueryItemExtensionInterface
{
    private $security;

    public function __construct(Security $security)
    {
        $this->security = $security;
    }

    public function applyToCollection(QueryBuilder $queryBuilder, QueryNameGeneratorInterface $queryNameGenerator, string $resourceClass, string $operationName = null): void
    {
        $this->addWhere($queryBuilder, $resourceClass);
    }

    public function applyToItem(QueryBuilder $queryBuilder, QueryNameGeneratorInterface $queryNameGenerator, string $resourceClass, array $identifiers, string $operationName = null, array $context = []): void
    {
        $this->addWhere($queryBuilder, $resourceClass);
    }

    private function addWhere(QueryBuilder $queryBuilder, string $resourceClass): void
    {
        if (Event::class !== $resourceClass && EventType::class !== $resourceClass && DeviceSetting::class !== $resourceClass) {
            return;
        }

        if ($this->security->isGranted('ROLE_ADMIN') || null === $user = $this->security->getUser()) {
            return;
        }

        $rootAlias = $queryBuilder->getRootAliases()[0];

        if(EventType::class === $resourceClass || DeviceSetting::class === $resourceClass) {
            $queryBuilder->innerJoin(sprintf('%s.device', $rootAlias), 'current_device');
        } else if (Event::class === $resourceClass) {
            $queryBuilder->innerJoin(sprintf('%s.type', $rootAlias), 'event_type');
            $queryBuilder->innerJoin('event_type.device', 'current_device');
        }

        $queryBuilder->andWhere('current_device.name = :current_device');

        $queryBuilder->setParameter('current_device', $user->getUsername());
    }
}