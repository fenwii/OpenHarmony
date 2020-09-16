/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file animator.h
 *
 * @brief Defines the attributes and common functions of the animator module.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_ANIMATOR_H
#define GRAPHIC_LITE_ANIMATOR_H

#include <cstdint>
#include "components/ui_view.h"
#include "list.h"
#include "common/task.h"

namespace OHOS {
class Animator;

/**
 * @brief Represents the animator callback.
 *
 * You need to implement the callback function to produce specific animator effects.
 *
 * @since 1.0
 * @version 1.0
 */
class AnimatorCallback : public HeapBase {
public:
    /**
     * @brief Called when each frame starts. This is a pure virtual function, which needs your inheritance
     *        and implementation.
     *
     * @param view Indicates the <b>UIView</b> instance, which is added from the constructor of
     *             the <b>Animator</b> class.
     * @since 1.0
     * @version 1.0
     */
    virtual void Callback(UIView* view) = 0;

    /**
     * @brief Called when an animator stops. This is a pure virtual function, which needs your inheritance and
     *        implementation.
     *
     * @param view Indicates the <b>UIView</b> instance, which is added from the constructor of
     *             the <b>Animator</b> class.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnStop(UIView& view) {};

    /**
     * @brief A default destructor used to delete an <b>AnimatorCallback</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~AnimatorCallback() {}
};

/**
 * @brief Represents an animator.
 *
 * This class is used to set the animator attributes, such as the duration, whether an animator is repeated,
 * start and stop of an animator.
 *
 * @see Animator
 * @since 1.0
 * @version 1.0
 */
class Animator : public HeapBase {
public:
    /**
     * @brief Enumerates the states of this animator.
     */
    enum : uint8_t {
        /** Stop */
        STOP,
        /** Start */
        START,
        /** Pause */
        PAUSE,
        /** Running (reserved and not used currently) */
        RUNNING
    };

    /**
     * @brief A default constructor used to create an <b>Animator</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Animator()
        : callback_(nullptr), view_(nullptr), state_(STOP), time_(0), repeat_(false), runTime_(0), lastRunTime_(0) {}

    /**
     * @brief A constructor used to create an <b>Animator</b> instance.
     *
     * @param callback Indicates the animator callback for producing animator effects.
     *                 For details, see {@link AnimatorCallback}.
     * @param view     Indicates the <b>UIView</b> instance bound to an animator, which can be used when invoking
     *                 the animator callback.
     * @param time     Indicates the duration of this animator, in milliseconds.
     * @param repeat   Specifies whether to repeat this animator. <b>true</b> indicates the animator is repeated,
     *                 and <b>false</b> (default value) indicates the animator is played once.
     * @since 1.0
     * @version 1.0
     */
    Animator(AnimatorCallback* callback, UIView* view, uint32_t time, bool repeat)
        : callback_(callback), view_(view), state_(STOP), time_(time), repeat_(repeat), runTime_(0), lastRunTime_(0) {}

    /**
     * @brief A destructor used to delete the <b>Animator</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Animator() {}

    /**
     * @brief Starts this animator.
     *
     * @see Stop
     * @since 1.0
     * @version 1.0
     */
    void Start();

    /**
     * @brief Stops this animator.
     *
     * @see Start
     * @since 1.0
     * @version 1.0
     */
    void Stop();

    /**
     * @brief Pauses this animator.
     *
     * @see Resume
     * @since 1.0
     * @version 1.0
     */
    void Pause();

    /**
     * @brief Resumes this animator from where it was paused.
     *
     * @see Pause
     * @since 1.0
     * @version 1.0
     */
    void Resume();

    /**
     * @brief Obtains the current state of this animator.
     *
     * @return Returns the current animator state, which can be {@link START}, {@link STOP}, or {@link PAUSE}.
     * @see SetState
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetState() const
    {
        return state_;
    }

    /**
     * @brief Sets the current state for this animator.
     *
     * @param state Indicates the current animator state to set, which can be {@link STOP}, {@link START},
     *              or {@link PAUSE}.
     * @see GetState
     * @since 1.0
     * @version 1.0
     */
    void SetState(uint8_t state)
    {
        state_ = state;
    }

    /**
     * @brief Obtains the total duration of this animator.
     *
     * @return Returns the total duration.
     * @see SetTime
     * @since 1.0
     * @version 1.0
     */
    uint32_t GetTime() const
    {
        return time_;
    }

    /**
     * @brief Sets the total duration for this animator.
     *
     * @param time Indicates the total duration to set, in milliseconds.
     * @see GetTime
     * @since 1.0
     * @version 1.0
     */
    void SetTime(uint32_t time)
    {
        time_ = time;
    }

    /**
     * @brief Obtains the running time of this animator.
     *
     * @return Returns the running time.
     * @see SetRunTime
     * @since 1.0
     * @version 1.0
     */
    uint32_t GetRunTime() const
    {
        return runTime_;
    }

    /**
     * @brief Sets the running time for this animator.
     *
     * @param runTime Indicates the running time to set, in milliseconds.
     * @see GetRunTime
     * @since 1.0
     * @version 1.0
     */
    void SetRunTime(uint32_t runTime)
    {
        runTime_ = runTime;
    }

    /**
     * @brief Checks whether this animator is repeated.
     *
     * @return Returns <b>true</b> if the animator is repeated; returns <b>false</b> if the animator is played once.
     * @since 1.0
     * @version 1.0
     */
    bool IsRepeat() const
    {
        return repeat_;
    }

    void Run();

protected:
    AnimatorCallback* callback_;
    UIView* view_;
    uint8_t state_;
    uint32_t time_;
    bool repeat_;
    uint32_t runTime_;
    uint32_t lastRunTime_;
};

/**
 * @brief Represents the animator manager.
 *
 * This is a singleton class used to manage <b>Animator</b> instances.
 *
 * @see Task
 * @since 1.0
 * @version 1.0
 */
class AnimatorManager : public Task {
public:
    /**
     * @brief Obtains the <b>AnimatorManager</b> instance.
     *
     * @return Returns the <b>AnimatorManager</b> instance.
     * @since 1.0
     * @version 1.0
     */
    static AnimatorManager* GetInstance()
    {
        static AnimatorManager animatorManager;
        return &animatorManager;
    }

    void Init() override;

    /**
     * @brief Adds the <b>Animator</b> instance to the <b>AnimatorManager</b> linked list for management,
     *        so that the {@link Run} function of the <b>Animator</b> class is called once for each frame.
     *
     * @param animator Indicates the pointer to the <b>Animator</b> instance to add.
     * @see Remove
     * @since 1.0
     * @version 1.0
     */
    void Add(Animator* animator);

    /**
     * @brief Removes the <b>Animator</b> instance from the <b>AnimatorManager</b> linked list.
     *
     * @param animator Indicates the pointer to the <b>Animator</b> instance to remove.
     * @see Add
     * @since 1.0
     * @version 1.0
     */
    void Remove(const Animator* animator);

    void AnimatorTask();

    void Callback() override
    {
        AnimatorTask();
    }

protected:
    List<Animator*> list_;
    AnimatorManager() {}
    virtual ~AnimatorManager() {}
    AnimatorManager(const AnimatorManager&) = delete;
    AnimatorManager& operator=(const AnimatorManager&) = delete;
    AnimatorManager(AnimatorManager&&) = delete;
    AnimatorManager& operator=(AnimatorManager&&) = delete;
};
}
#endif
