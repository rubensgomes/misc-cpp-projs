/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_done_listener.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_DONE_LISTENER_HPP_
#define THREADPOOL_TASK_DONE_LISTENER_HPP_

#include <boost/noncopyable.hpp>

/**
 * An abstract base class that defines a type
 * containing the behaviour for a listener interested
 * in knowing when its task is done running.
 *
 * @author Rubens Gomes
 */
class TaskListener: private boost::noncopyable
{
public:
    // dtor
    virtual ~TaskListener() = 0;

    /**
     * The clone method is required by pointer
     * containers (for example boost::ptr_vector<>)
     * when storing instance pointers.
     *
     * @return a clone instance.
     */
    virtual TaskListener * clone(void) const = 0;

    /**
     * The client will get a call back on this
     * method when that task is completed.
     */
    virtual void notifyTaskDone() const = 0;

    /**
     * The equal comparison operator.
     *
     * @param the object to compare to.
     * @return true if this and the other object have the
     * same address; false, otherwise.
     */
    bool operator==(const TaskListener &) const;

    /**
     * the not equal comparison operator.
     *
     * @param the object to compare to.
     * @return true if this and the other object have
     * different address; false, otherwise.
     */
    bool operator!=(const TaskListener &) const;
};

inline TaskListener::~TaskListener()
{}

// We allow cloning to allow this object to be
// stored in pointer containers.  And we need
// to tell the pointer containers how cloning
// is to be done as follows. This is simply by
// defining a free-standing function, new_clone(),
// as follows:
inline TaskListener * new_clone(const TaskListener & rhs)
{
  return rhs.clone();
}

#endif /* THREADPOOL_TASK_DONE_LISTENER_HPP_ */
