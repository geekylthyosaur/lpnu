// PWA

// Install service worker
self.addEventListener('install', (event) => {
  event.waitUntil(
    caches.open('my-pwa-cache')
      .then((cache) => {
        return cache.addAll([
          '/',
          '/index.html',
          '/style.css',
          '/script.js',
          '/images/'
        ]);
      })
  );
});
// Fetch resources with cache fallback
self.addEventListener('fetch', (event) => {
  event.respondWith(
    caches.match(event.request)
      .then((response) => {
        if (response) {
          return response;
        }
        return fetch(event.request)
          .then((response) => {
            return caches.open('my-pwa-cache')
              .then((cache) => {
                cache.put(event.request, response.clone())
                return response;
              });
          });
      })
  );
});
// Update cache when new service worker is activated
self.addEventListener('activate', (event) => {
  event.waitUntil(
    caches.keys().then((cacheNames) => {
      return Promise.all(
        cacheNames.filter((cacheName) => {
          return cacheName.startsWith('my-pwa-cache') &&
            cacheName !== 'my-pwa-cache';
        }).map((cacheName) => {
          return caches.delete(cacheName);
        })
      );
    })
  );
});

self.addEventListener('fetch', (event) => {
  event.respondWith(
    caches.match(event.request)
      .then((response) => {
        if (response) {
          return response;
        }
        return fetch(event.request);
      }),
  );
});
