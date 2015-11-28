
# Logger
`Logger` is the logging tool extracted from `sugen`, and I refactored and improved the original
codes to so that it can be used more easily in other projects.

`Logger` is now only available in single-thread, using it in multi-thread will cause unexpected 
error. It's in my plan to support `Logger` in multi-thread.
