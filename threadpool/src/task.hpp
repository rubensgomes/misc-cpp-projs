/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_HPP_
#define THREADPOOL_TASK_HPP_

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "task_listener.hpp"

/**
 * An abstract base class that defines a
 * type for a task to be executed from a
 * separate thread.
 *
 * @author Rubens Gomes
 */
class Task : private boost::noncopyable
{
public:
    // ctor
    Task();

    // dtor
    virtual ~Task();

    /**
     * The clone method is required by pointer
     * containers (for example boost::ptr_vector<>)
     * when storing instance pointers.
     *
     * @return a clone instance.
     */
    virtual Task * clone(void) const = 0;

    /**
     * The run method should contain the code that is
     * to be executed from a thread.  In order for this
     * task to be interrupted the user should provide
     * an interrupt thread point by calling thread wait(),
     * for example.
     */
    void run(void) const;

    /**
     * Registers an observer which wants be notified
     * when this task is done.
     *
     * @param a listener that is to be registered.
     */
    void addListener(TaskListener *);

    /**
     * Removes a previously registered observer of
     * this task.
     *
     * @param a listener that is to be un-registered.
     */
    void removeListener(TaskListener &);

    /**
     * Every task is uniquely identified by
     * a unique id.
     *
     * @return my id.
     */
    double getId(void) const;

private:
    /**
     * This method should implement whatever the task
     * needs to accomplish when it is executed by a
     * separate thread.
     */
    virtual void do_run(void) const = 0;

    /**
     * The intent of this method is to notify
     * registered listeners when this task run
     * is completed.  This function is automatically
     * called when do_run() returns.
     */
    void notifyListeners(void) const;

    double m_id;
    boost::ptr_vector<TaskListener> m_listeners;
    static double s_counter;
};

// We allow cloning to allow this object to be
// stored in pointer containers.  And we need
// to tell the pointer containers how cloning
// is to be done as follows. This is simply by
// defining a free-standing function, new_clone(),
// as follows:
inline Task * new_clone(const Task & rhs)
{
  return rhs.clone();
}

#endif /* THREADPOOL_TASK_HPP_ */
