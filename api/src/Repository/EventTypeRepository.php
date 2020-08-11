<?php

namespace App\Repository;

use App\Entity\EventType;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Common\Persistence\ManagerRegistry;

class EventTypeRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, EventType::class);
    }

    public function getByNameAndDevice(?string $name, ?string $device)
    {
        return $this->createQueryBuilder('t')
            ->innerJoin('t.device', 'd')
            ->where('t.name = :name')
            ->andWhere('d.name = :device')
            ->setParameter('name', $name)
            ->setParameter('device', $device)
            ->getQuery()->getOneOrNullResult();
    }
}