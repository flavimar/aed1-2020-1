/* with the same code as before: */
Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = &my_function;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

/* Now the event loop */
SDL_Event event;
while (SDL_PollEvent (&event))
{
    switch(event.type)
    {
        case SDL_USEREVENT: {
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            void (*p) (void*) = event.user.data1;
            p(event.user.data2);
            break;
        }
        /* ... */
    }
