#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
public:
    /*!
     * \brief static function which instatiate if no instatiatation exist other wise return instatiated object of class that exist
     * \return instatiated object of class
     */
    static T* instance()
    {
        if (!instance_) {
            instance_ = new T;
        }
        return instance_;
    }

    /*!
     * \brief static function that destroy instatiated object of class
     */
    static void destroy_instance()
    {
        delete instance_;
        instance_ = 0;
    }

private:
    static T* instance_;
};

template <class T> T* Singleton<T>::instance_ = 0;


#endif // SINGLETON_H
