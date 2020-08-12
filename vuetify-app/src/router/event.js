export default {
  path: '/events',
  name: 'events',
  component: () => import('../components/event/Layout'),
  redirect: { name: 'EventList' },
  children: [
    {
      name: 'EventList',
      path: '',
      component: () => import('../views/event/List')
    },
    {
      name: 'EventCreate',
      path: 'new',
      component: () => import('../views/event/Create')
    },
    {
      name: 'EventUpdate',
      path: ':id/edit',
      component: () => import('../views/event/Update')
    },
    {
      name: 'EventShow',
      path: ':id',
      component: () => import('../views/event/Show')
    }
  ]
};
