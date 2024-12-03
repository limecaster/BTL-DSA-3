/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/*
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "tensor/xtensor_lib.h"
#include "loader/dataset.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader
{
public:
    class Iterator; // forward declaration for class Iterator

private:
    Dataset<DType, LType> *ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int nbatch;
    ulong_tensor item_indices;
    int m_seed;

public:
    DataLoader(Dataset<DType, LType> *ptr_dataset,
               int batch_size, bool shuffle = true,
               bool drop_last = false, int seed = -1)
        : ptr_dataset(ptr_dataset),
          batch_size(batch_size),
          shuffle(shuffle),
          m_seed(seed)
    {
        nbatch = ptr_dataset->len() / batch_size;
        item_indices = xt::arange(0, ptr_dataset->len());
        if (shuffle)
        {
            if (m_seed >= 0)
            {
                xt::random::seed(m_seed);
            }
            xt::random::shuffle(item_indices);
        };
    }
    virtual ~DataLoader() {}

    // New method: from V2: begin
    int get_batch_size() { return batch_size; }
    int get_sample_count() { return ptr_dataset->len(); }
    int get_total_batch() { return int(ptr_dataset->len() / batch_size); }

    // New method: from V2: end
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
public:
    class Iterator
    {
    private:
        DataLoader<DType, LType> *ptr_loader;
        int index;

    public:
        Iterator(DataLoader<DType, LType> *ptr_loader, int index) : ptr_loader(ptr_loader), index(index) {}

        Iterator &operator=(const Iterator &other)
        {
            ptr_loader = other.ptr_loader;
            index = other.index;
            return *this;
        }

        bool operator!=(const Iterator &other)
        {
            return index != other.index;
        }

        Iterator &operator++()
        {
            index++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator it = *this;
            index++;
            return it;
        }

        Batch<DType, LType> operator*()
        {
            int start = index * ptr_loader->batch_size;
            int end;

            if (index == ptr_loader->nbatch - 1 && !ptr_loader->drop_last)
            {
                end = ptr_loader->ptr_dataset->len();
            }
            else
            {
                end = std::min(start + ptr_loader->batch_size, ptr_loader->ptr_dataset->len());
            }

            if (end - start < ptr_loader->batch_size && ptr_loader->drop_last)
            {
                return Batch<DType, LType>(xt::xarray<DType>(), xt::xarray<LType>());
            }

            // Get the batch data shape based on the range of samples in the current batch
            xt::svector<unsigned long> data_shape = ptr_loader->ptr_dataset->get_data_shape();
            xt::svector<unsigned long> label_shape = ptr_loader->ptr_dataset->get_label_shape();

            // Adjust the batch size to the remaining samples for the last batch
            data_shape[0] = end - start;

            xt::xarray<DType> batch_data = xt::zeros<DType>(data_shape);
            xt::xarray<LType> batch_label;

            if (label_shape.size() > 0)
            {
                label_shape[0] = end - start;
                batch_label = xt::empty<LType>(label_shape);
            }
            else
            {
                // Create an empty label array if the label shape is not available
                batch_label = xt::xarray<LType>();
            }

            // Populate batch_data and batch_label
            for (int i = start; i < end; i++)
            {
                int data_index = ptr_loader->item_indices[i];

                DataLabel<DType, LType> data_label = ptr_loader->ptr_dataset->getitem(data_index);

                xt::view(batch_data, i - start, xt::all()) = data_label.getData();
                if (label_shape.size() > 0)
                {
                    xt::view(batch_label, i - start, xt::all()) = data_label.getLabel();
                }
            }

            return Batch<DType, LType>(batch_data, batch_label);
        }
    };

    Iterator begin()
    {
        return Iterator(this, 0);
    }

    Iterator end()
    {
        return Iterator(this, nbatch);
    }

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};

#endif /* DATALOADER_H */
