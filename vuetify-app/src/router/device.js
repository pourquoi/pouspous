export default {
  path: '/devices',
  name: 'devices',
  component: () => import('../components/device/Layout'),
  redirect: { name: 'DeviceList' },
  children: [
    {
      name: 'DeviceList',
      path: '',
      component: () => import('../views/device/List')
    },
    {
      name: 'DeviceCreate',
      path: 'new',
      component: () => import('../views/device/Create')
    },
    {
      name: 'DeviceUpdate',
      path: ':id/edit',
      component: () => import('../views/device/Update')
    },
    {
      name: 'DeviceShow',
      path: ':id',
      component: () => import('../views/device/Show')
    }
  ]
};
