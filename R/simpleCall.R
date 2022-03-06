
#' Tickle a valgrind issue
#'
#' @param x A numeric vector
simpleCall <- function(x=c(10,20,30)) {
    invisible(.Call(simpleCall_impl, x))
}

